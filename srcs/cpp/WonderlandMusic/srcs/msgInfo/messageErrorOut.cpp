#include "messageErrorOut.h"
#include <cmake_include_to_c_cpp_header_env.h>
#include <qdir.h>

#include "../applications/applicationInstance.h"

#include "../tools/dateTimeFormat.h"
#ifdef Q_OS_WIN
#include <windows.h>

// 核心：直接输出 UTF-16，不走 qDebug、不走本地编码
void normalConsoleOut( const QString &text ) {
	HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );
	if( h == INVALID_HANDLE_VALUE ) return;
	// QString → UTF-16（直接给控制台）
	const ushort *utf16 = text.utf16( );
	const wchar_t *w = reinterpret_cast< const wchar_t * >( utf16 );
	WriteConsoleW( h, w, text.length( ), nullptr, nullptr );
	WriteConsoleW( h, L"\r\n", 2, nullptr, nullptr );
}

#else
inline void winConsolePrint( const QString &text ) {
	qDebug( ) << outString.toUtf8( ).constData( );
}
#endif

MessageErrorOut::Translate::Translate( ) {
	sourceFile = QObject::tr( "源文件" );
	sourceFunction = QObject::tr( "源函数" );
	sourceLine = QObject::tr( "源行号" );
	createDirError = QObject::tr( "创建目录失败" );
	openFileError = QObject::tr( "打开文件失败" );
}
MessageErrorOut::MessageErrorOut( bool is_write_file, const QString &log_home_path, const std::source_location &source_location ) : logHomePtah( log_home_path ), location( source_location ), isWriteFile( is_write_file ) {

}
MessageErrorOut & MessageErrorOut::operator<<( const QString &msg ) {
	outMsgVector.emplace_back( msg );
	return *this;
}
MessageErrorOut & MessageErrorOut::operator<<( const QStringList &msg ) {
	return MessageErrorOut::operator<<( "QStringList[" + QString::number( msg.count( ) ) + "]{\n\t\t" + msg.join( ",\n\t\t" ) + "\n\t};" );
}
MessageErrorOut::~MessageErrorOut( ) {

	QString outString;
	QString jion( "\t" );
	size_t count = outMsgVector.size( );
	size_t index;
	if( count > 0 ) {
		auto data = outMsgVector.data( );
		for( index = 0; index < count; ++index )
			jion += data[ index ];
	}
	outMsgVector.clear( );
	DateTimeFormat dateTimeFormat;
	formatMessageOut( dateTimeFormat, outString, location, jion );
	normalConsoleOut( outString );
	if( isWriteFile == false )
		return;
	auto *applicationInstance = ApplicationInstance::getApplicationInstance( );
	if( applicationInstance == nullptr )
		return;
	auto &appStartRunDataTime = applicationInstance->getAppStartRunDataTime( );
	auto date = appStartRunDataTime.date( );
	QString dateTimeFormatString;
	dateTimeFormat.formatData( dateTimeFormatString, date );
	QString writeFilePath = logHomePtah + "/" + dateTimeFormatString + ".log";
	QFileInfo fileInfo( writeFilePath );
	auto dir = fileInfo.dir( );
	writeFilePath = fileInfo.absoluteFilePath( );
	logHomePtah = dir.absolutePath( );
	if( dir.exists( ) == false ) {
		if( dir.mkdir( logHomePtah ) == false ) {
			outString.clear( );
			formatMessageOut( dateTimeFormat, outString, std::source_location::current( ), translate.createDirError + " : " + logHomePtah );
			normalConsoleOut( outString );
			return;
		}
	}
	QFile openFile( writeFilePath );
	QFlags< QIODevice::OpenMode::enum_type > flags = QIODeviceBase::ReadWrite | QIODeviceBase::Append;
	if( openFile.open( flags ) == false ) {
		outString.clear( );
		formatMessageOut( dateTimeFormat, outString, std::source_location::current( ), translate.openFileError + " : " + writeFilePath );
		normalConsoleOut( outString );
		return;
	}
	openFile.write( outString.toUtf8( ) );
	openFile.close( );
}
QString & MessageErrorOut::formatMessageOut( const DateTimeFormat &date_time_format, QString &result_msg, const std::source_location &source_location, const QString &msg ) const {
	uint_least32_t msgCodeLine = location.line( );
	auto msgCodeFileName = location.file_name( );
	auto msgCodeFunctionName = location.function_name( );
	QDir cmakeRootPath( Cmake_Source_Dir );
	auto relativeFilePath = cmakeRootPath.relativeFilePath( msgCodeFileName );

	QString currentDataTimeToString;
	DateTimeFormat dateTimeFormat;
	dateTimeFormat.formatData( currentDataTimeToString ).append( dateTimeFormat.formatTime( ) );

	result_msg.append( "\n-----\n :: \n : " ).append( translate.sourceFile ).append( " = " ).append( relativeFilePath ).append( "\n : " ).append( translate.sourceFunction ).append( " = " ).append( msgCodeFunctionName ).append( "\n : " ).append( translate.sourceLine ).append( " = " ).append( QString::number( msgCodeLine ) ).append( "\n : " ).append( currentDataTimeToString ).append( " ->\n ::\n" ).append( msg ).append( "\n-----\n" );

	return result_msg;
}
