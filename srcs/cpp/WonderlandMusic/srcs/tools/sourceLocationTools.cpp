#include "sourceLocationTools.h"
#include <QFileInfo>
#include <QString>
#include <source_location>

#include "../application/appInstance/appDataManage/translate/messageTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../msgInfo/cmakeInfo.h"

void SourceLocationTools::formatString( QString &format_string, QString &source_file, QString &source_function, QString &source_line, const std::source_location &location, const QString &msg ) {
	uint_least32_t msgCodeLine = location.line( );
	QString msgCodeFileName = location.file_name( );
	QString msgCodeFunctionName = location.function_name( );
	QFileInfo info( msgCodeFileName );
	auto absoluteFilePath = info.absoluteFilePath( );
	QString cmakeSourceDir;
	CmakeInfo::getGeneratePorjectCmakeSourceDir( cmakeSourceDir );
	msgCodeFileName = absoluteFilePath.remove( cmakeSourceDir );

	QString currentDataTimeToString;
	DateTimeFormat dateTimeFormat;
	dateTimeFormat.formatData( currentDataTimeToString ).append( dateTimeFormat.formatTime( ) );

	bool message = AppTranslateTools::getMessage( [&] ( MessageTranslate &message_translate ) {
		source_file = message_translate.getSourceFile( );
		source_function = message_translate.getSourceFunction( );
		source_line = message_translate.getSourceLine( );
		return true;
	} );
	if( message == false ) {
		source_file = QObject::tr( "源文件" );
		source_function = QObject::tr( "源函数" );
		source_line = QObject::tr( "源行号" );
	}
	format_string.append( "\n-----\n :: \n : " ).append( source_file ).append( " = " ).append( msgCodeFileName ).append( "\n : " ).append( source_function ).append( " = " ).append( msgCodeFunctionName ).append( "\n : " ).append( source_line ).append( " = " ).append( QString::number( msgCodeLine ) ).append( "\n : " ).append( currentDataTimeToString ).append( " ->\n ::\n" ).append( msg ).append( "\n-----\n" );
}

void SourceLocationTools::formatString( QString &format_string, const std::source_location &location, const QString &msg ) {
	QString source_file, source_function, source_line;
	SourceLocationTools::formatString( format_string, source_file, source_function, source_line, location, msg );
}

void SourceLocationTools::formatSourceFilePath( QString &source_file, QString &source_function, QString &source_line, const std::source_location &location ) {
	source_line = QString::number( location.line( ) );
	source_file = location.file_name( );
	source_function = location.function_name( );
	QFileInfo info( source_file );
	auto absoluteFilePath = info.absoluteFilePath( );
	QString cmakeSourceDir;
	CmakeInfo::getGeneratePorjectCmakeSourceDir( cmakeSourceDir );
	source_file = absoluteFilePath.remove( cmakeSourceDir );
}

void SourceLocationTools::formatString( QString &result_msg, const DateTimeFormat &date_time_format, const std::source_location &source_location, const QString &msg ) {
	uint_least32_t msgCodeLine = source_location.line( );
	QString msgCodeFileName = source_location.file_name( );
	QString msgCodeFunctionName = source_location.function_name( );
	QFileInfo info( msgCodeFileName );

	auto absoluteFilePath = info.absoluteFilePath( );
	QString cmakeSourceDir;
	CmakeInfo::getGeneratePorjectCmakeSourceDir( cmakeSourceDir );
	msgCodeFileName = absoluteFilePath.remove( cmakeSourceDir );

	QString currentDataTimeToString;
	DateTimeFormat dateTimeFormat;
	dateTimeFormat.formatData( currentDataTimeToString ).append( dateTimeFormat.formatTime( ) );

	QString sourceFile;
	QString sourceFunction;
	QString sourceLine;
	bool message = AppTranslateTools::getMessage( [&sourceFile, &sourceFunction, &sourceLine] ( MessageTranslate &message_translate ) {
		sourceFile = message_translate.getSourceFile( );
		sourceFunction = message_translate.getSourceFunction( );
		sourceLine = message_translate.getSourceLine( );
		return true;
	} );
	if( message == false ) {
		sourceFile = QObject::tr( "源文件" );
		sourceFunction = QObject::tr( "源函数" );
		sourceLine = QObject::tr( "源行号" );
	}

	result_msg.append( "\n-----\n :: \n : " ).append( sourceFile ).append( " = " ).append( msgCodeFileName ).append( "\n : " ).append( sourceFunction ).append( " = " ).append( msgCodeFunctionName ).append( "\n : " ).append( sourceLine ).append( " = " ).append( QString::number( msgCodeLine ) ).append( "\n : " ).append( currentDataTimeToString ).append( " ->\n ::\n" ).append( msg ).append( "\n-----\n" );
}
