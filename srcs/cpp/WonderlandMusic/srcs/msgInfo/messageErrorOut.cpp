#include "messageErrorOut.h"
#include <cmake_include_to_c_cpp_header_env.h>
#include <qdir.h>

#include "../applications/application.h"
#include "../applications/applicationInstance.h"
MessageErrorOut::MessageErrorOut( const QString &log_home_path, const std::source_location &source_location ) : logHomePtah( log_home_path ), location( source_location ) { }
MessageErrorOut & MessageErrorOut::operator<<( const QString &msg ) {
	outMsgVector.emplace_back( msg );
	return *this;
}
MessageErrorOut::~MessageErrorOut( ) {
	uint_least32_t msgCodeLine = location.line( );
	auto msgCodeFileName = location.file_name( );
	auto msgCodeFunctionName = location.function_name( );
	QDir cmakeRootPath( Cmake_Source_Dir );
	auto relativeFilePath = cmakeRootPath.relativeFilePath( msgCodeFileName );
	QString outString;
	QString jion( "\t" );
	size_t count = outMsgVector.size( );
	size_t index;
	if( count > 0 ) {
		auto data = outMsgVector.data( );
		for( index = 0; index < count; ++index )
			jion += data[ index ];
	}
	outString.append( "\n-----\n :: \n : 源文件 = " ).append( relativeFilePath ).append( "\n : 函数 = " ).append( msgCodeFunctionName ).append( "\n : 行号 = " ).append( QString::number( msgCodeLine ) ).append( "\n : " ).append( QDateTime::currentDateTime( ).toString( "yyyy 年 MM 月 dd 日 hh : mm : ss . z" ) ).append( " ->\n ::\n" ).append( jion ).append( "\n-----\n" );

	std::string stdString = outString.toStdString( );
	qDebug( ) << stdString.c_str( );
	auto &appStartRunDataTime = ApplicationInstance::getInstance( )->getApplication( )->getAppStartRunDataTime( );
	QString writeFilePath = logHomePtah + "/" + appStartRunDataTime.toString( "yyyy年MM月dd日" ) + ".log";
	QFileInfo fileInfo( writeFilePath );
	auto dir = fileInfo.dir( );
	writeFilePath = fileInfo.absoluteFilePath( );
	logHomePtah = dir.absolutePath( );
	if( dir.exists( ) == false ) {
		if( dir.mkdir( logHomePtah ) == false ) {
			auto sourceLocation = std::source_location::current( );
			relativeFilePath = cmakeRootPath.relativeFilePath( sourceLocation.file_name( ) );
			qDebug( ) << QObject::tr( "::%1 [ %2 ]( %3 )::\n->无法创建目录 : %4" ).arg( relativeFilePath ).arg( sourceLocation.function_name( ) ).arg( QString::number( sourceLocation.line( ) ) ).arg( logHomePtah ).toStdString( ).c_str( );
			return;
		}
	}
	QFile openFile( writeFilePath );
	QFlags< QIODevice::OpenMode::enum_type > flags = QIODeviceBase::ReadWrite;
	if( fileInfo.exists( ) )
		flags = flags | QIODeviceBase::Append;
	if( openFile.open( flags ) == false ) {
		auto sourceLocation = std::source_location::current( );
		relativeFilePath = cmakeRootPath.relativeFilePath( sourceLocation.file_name( ) );
		qDebug( ) << QObject::tr( "::%1 [ %2 ]( %3 )::\n->无法打开文件 : %4" ).arg( relativeFilePath ).arg( sourceLocation.function_name( ) ).arg( QString::number( sourceLocation.line( ) ) ).arg( writeFilePath ).toStdString( ).c_str( );
		return;
	}
	const uchar utfBom[ ] = { 0xEF, 0xBB, 0xBF };
	openFile.write( ( const char * ) utfBom, sizeof utfBom );
	openFile.write( outString.toUtf8( ) );
	openFile.close( );
}
