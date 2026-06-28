#include "messageErrorOut.h"
#include <cmake_include_to_c_cpp_header_env.h>
#include <qdir.h>

#include "messageString.h"

#include "../application/appDataManage.h"
#include "../application/appDateTimerManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/messageTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#ifdef Q_OS_WIN
#include <windows.h>

// 核心：直接输出 UTF-16，不走 qDebug、不走本地编码
void StdErrorConsoleOut( const QString &text ) {
	HANDLE h = GetStdHandle( STD_ERROR_HANDLE );
	if( h == INVALID_HANDLE_VALUE )
		return;
	// QString → UTF-16（直接给控制台）
	auto stdU16String = text.toStdU16String( );
	auto data = stdU16String.data( );
	WriteConsoleW( h, data, stdU16String.length( ), nullptr, nullptr );
	WriteConsoleW( h, L"\r\n", 2, nullptr, nullptr );
}

#else
	#define StdErrorConsoleOut( text ) qDebug( ) << text.toUtf8( ).constData( )
#endif

MessageErrorOut::MessageErrorOut( bool is_write_file, const QString &log_home_path, const std::source_location &source_location ) : logHomePtah( log_home_path ), location( source_location ), isWriteFile( is_write_file ) {
}

MessageErrorOut::MessageErrorOut( const QString &log_home_path, const std::source_location &source_location ) : MessageErrorOut( true, log_home_path, source_location ) {
}

MessageErrorOut::MessageErrorOut( const std::source_location &source_location ) : MessageErrorOut( true, "log", source_location ) {
}

MessageErrorOut & MessageErrorOut::operator<<( const MessageString &msg ) {
	outMsgVector.emplace_back( msg.toQString( ) );
	return *this;
}

const QString & MessageErrorOut::getJoinString( ) const {
	return jointString;
}

void MessageErrorOut::setJoinString( const QString &join ) {
	this->jointString = join;
}

const QString & MessageErrorOut::getStartString( ) const {
	return startString;
}

void MessageErrorOut::setStartString( const QString &start_string ) {
	startString = start_string;
}

const QString & MessageErrorOut::getEndString( ) const {
	return endString;
}

void MessageErrorOut::setEndString( const QString &end_string ) {
	endString = end_string;
}

const std::vector< MessageString > & MessageErrorOut::getOutMsgVector( ) const {
	return this->outMsgVector;
}

MessageErrorOut::~MessageErrorOut( ) {
	writeLog( );
}

QString MessageErrorOut::toQString( ) const {
	return toQString( DateTimeFormat( ) );
}

QString MessageErrorOut::toQString( const DateTimeFormat &date_time_format ) const {
	QString outString;
	size_t count = outMsgVector.size( );
	size_t index;
	QString complete = startString;
	if( count > 0 ) {
		auto data = outMsgVector.data( );
		count -= 1;
		for( index = 0; index < count; ++index )
			complete += data[ index ].toQString( ) + jointString;
		complete += data[ index ].toQString( ) + endString;
	}
	formatMessageOut( date_time_format, outString, location, complete );
	return outString;
}

QString MessageErrorOut::writeLog( const QString &wirte_log_path, const DateTimeFormat &date_time_format ) const {
	QString outString = toQString( date_time_format );
	StdErrorConsoleOut( outString );
	if( isWriteFile == false )
		return outString;
	auto *applicationInstance = AppInstance::getAppInstance( );
	if( applicationInstance == nullptr )
		return outString;
	auto appStartRunDataTime = *applicationInstance->getAppDateTimerManage( )->getStartDateTime( );
	auto date = appStartRunDataTime.date( );
	QString dateTimeFormatString;
	date_time_format.formatData( dateTimeFormatString, date );
	QString writeFilePath = wirte_log_path;
	if( wirte_log_path.isEmpty( ) )
		writeFilePath = logHomePtah + "/" + dateTimeFormatString + ".log";
	QFileInfo fileInfo( writeFilePath );
	auto dir = fileInfo.dir( );
	writeFilePath = fileInfo.absoluteFilePath( );
	auto logHomePtah = dir.absolutePath( );
	auto translate = applicationInstance->getAppDataManage( )->getTranslate( );
	if( dir.exists( ) == false ) {
		if( dir.mkdir( logHomePtah ) == false ) {
			outString.clear( );
			auto messageTranslate = translate->getMessage( );
			formatMessageOut( date_time_format, outString, std::source_location::current( ), messageTranslate->getCreateDirError( ) + " : " + logHomePtah );
			StdErrorConsoleOut( outString );
			return outString;
		}
	}
	QFile openFile( writeFilePath );
	QFlags< QIODevice::OpenMode::enum_type > flags = QIODeviceBase::ReadWrite | QIODeviceBase::Append;
	if( openFile.open( flags ) == false ) {
		outString.clear( );
		auto messageTranslate = translate->getMessage( );
		formatMessageOut( date_time_format, outString, std::source_location::current( ), messageTranslate->getOpenFileError( ) + " : " + writeFilePath );
		StdErrorConsoleOut( outString );
		return outString;
	}
	openFile.write( outString.toUtf8( ) );
	openFile.close( );
	return outString;
}

QString MessageErrorOut::writeLog( const DateTimeFormat &date_time_format ) const {
	return writeLog( "", date_time_format );
}

QString MessageErrorOut::writeLog( const QString &wirte_log_path ) const {
	return writeLog( wirte_log_path, DateTimeFormat( ) );
}

QString MessageErrorOut::writeLog( ) const {
	return writeLog( "", DateTimeFormat( ) );
}

QString & MessageErrorOut::formatMessageOut( const DateTimeFormat &date_time_format, QString &result_msg, const std::source_location &source_location, const QString &msg ) const {
	uint_least32_t msgCodeLine = location.line( );
	QString msgCodeFileName = location.file_name( );
	QString msgCodeFunctionName = location.function_name( );
	QFileInfo info( msgCodeFileName );
	//QDir cmakeRootPath( Cmake_Source_Dir );
	auto absoluteFilePath = info.absoluteFilePath( );
	msgCodeFileName = absoluteFilePath.remove( Cmake_Source_Dir );

	QString currentDataTimeToString;
	DateTimeFormat dateTimeFormat;
	dateTimeFormat.formatData( currentDataTimeToString ).append( dateTimeFormat.formatTime( ) );

	auto *applicationInstance = AppInstance::getAppInstance( );
	auto translate = applicationInstance->getAppDataManage( )->getTranslate( );
	auto messageTranslate = translate->getMessage( );
	QString sourceFile = messageTranslate->getSourceFile( );
	QString sourceFunction = messageTranslate->getSourceFunction( );
	QString sourceLine = messageTranslate->getSourceLine( );
	result_msg.append( "\n-----\n :: \n : " ).append( sourceFile ).append( " = " ).append( msgCodeFileName ).append( "\n : " ).append( sourceFunction ).append( " = " ).append( msgCodeFunctionName ).append( "\n : " ).append( sourceLine ).append( " = " ).append( QString::number( msgCodeLine ) ).append( "\n : " ).append( currentDataTimeToString ).append( " ->\n ::\n" ).append( msg ).append( "\n-----\n" );

	return result_msg;
}
