#include "messageErrorOut.h"
#include <qdir.h>
#include "messageString.h"

#include "../application/appInstance/appDateTimerManage.h"
#include "../application/appInstance/appDataManage/translate/messageTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../tools/instanceTools.h"
#include "../tools/sourceLocationTools.h"
#ifdef Q_OS_WIN
#include <windows.h>
// 核心：直接输出 UTF-16，不走 qDebug、不走本地编码
static void StdErrorConsoleOut( const QString &text ) {
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
	SourceLocationTools::formatString( outString, date_time_format, location, complete );
	return outString;
}

QString MessageErrorOut::writeLog( const QString &wirte_log_path, const DateTimeFormat &date_time_format ) const {
	QString outString = toQString( date_time_format );
	StdErrorConsoleOut( outString );
	if( isWriteFile == false )
		return outString;
	QDateTime appStartRunDataTime;
	const QDateTime *startDateTime = nullptr;
	AppDateTimerManage *appDateTimerManage = InstanceTools::getAppDateTimerManage( );
	if( appDateTimerManage ) {
		startDateTime = appDateTimerManage->getStartDateTime( );
		if( startDateTime )
			appStartRunDataTime = *startDateTime;
	}
	if( startDateTime == nullptr )
		appStartRunDataTime = QDateTime::currentDateTime( );
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

	if( dir.exists( ) == false ) {
		if( dir.mkdir( logHomePtah ) == false ) {
			outString.clear( );
			QString createDirError;
			if( AppTranslateTools::getMessage( [&createDirError] ( MessageTranslate &translate ) {
				createDirError = translate.getCreateDirError( );
				return true;
			} ) == false )
				createDirError = QObject::tr( "创建目录失败" );

			SourceLocationTools::formatString( outString, date_time_format, std::source_location::current( ), createDirError + " : " + logHomePtah );
			StdErrorConsoleOut( outString );
			return outString;
		}
	}
	QFile openFile( writeFilePath );
	QFlags< QIODevice::OpenMode::enum_type > flags = QIODeviceBase::ReadWrite | QIODeviceBase::Append;
	if( openFile.open( flags ) == false ) {
		outString.clear( );
		QString openFileError;
		if( AppTranslateTools::getMessage( [&openFileError] ( MessageTranslate &translate ) {
			openFileError = translate.getOpenFileError( );
			return true;
		} ) == false )
			openFileError = QObject::tr( "打开文件失败" );
		SourceLocationTools::formatString( outString, date_time_format, std::source_location::current( ), openFileError + " : " + writeFilePath );
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
