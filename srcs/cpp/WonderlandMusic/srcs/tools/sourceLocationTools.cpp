#include "sourceLocationTools.h"

#include <QFileInfo>
#include <QString>
#include <source_location>

#include "../../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/messageTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

void SourceLocationTools::formatString( QString &format_string, QString &source_file, QString &source_function, QString &source_line, const std::source_location &location, const QString &msg ) {
	uint_least32_t msgCodeLine = location.line( );
	QString msgCodeFileName = location.file_name( );
	QString msgCodeFunctionName = location.function_name( );
	QFileInfo info( msgCodeFileName );
	auto absoluteFilePath = info.absoluteFilePath( );
	msgCodeFileName = absoluteFilePath.remove( Cmake_Source_Dir );

	QString currentDataTimeToString;
	DateTimeFormat dateTimeFormat;
	dateTimeFormat.formatData( currentDataTimeToString ).append( dateTimeFormat.formatTime( ) );

	MessageTranslate *messageTranslate = nullptr;
	auto *applicationInstance = AppInstance::getAppInstance( );
	if( applicationInstance ) {
		auto appDataManage = applicationInstance->getAppDataManage( );
		if( appDataManage ) {
			auto translate = appDataManage->getTranslate( );
			if( translate ) {
				messageTranslate = translate->getMessage( );
				source_file = messageTranslate->getSourceFile( );
				source_function = messageTranslate->getSourceFunction( );
				source_line = messageTranslate->getSourceLine( );
			}
		}
	}
	if( messageTranslate == nullptr ) {
		messageTranslate = new MessageTranslate;
		if( messageTranslate->init( ) ) {
			source_file = messageTranslate->getSourceFile( );
			source_function = messageTranslate->getSourceFunction( );
			source_line = messageTranslate->getSourceLine( );
		} else {
			source_file = QObject::tr( "源文件" );
			source_function = QObject::tr( "源函数" );
			source_line = QObject::tr( "源行号" );
		}
		delete messageTranslate;
	}
	format_string.append( "\n-----\n :: \n : " ).append( source_file ).append( " = " ).append( msgCodeFileName ).append( "\n : " ).append( source_function ).append( " = " ).append( msgCodeFunctionName ).append( "\n : " ).append( source_line ).append( " = " ).append( QString::number( msgCodeLine ) ).append( "\n : " ).append( currentDataTimeToString ).append( " ->\n ::\n" ).append( msg ).append( "\n-----\n" );
}

void SourceLocationTools::formatSourceFilePath( QString &source_file, QString &source_function, QString &source_line, const std::source_location &location ) {
	source_line = QString::number( location.line( ) );
	source_file = location.file_name( );
	source_function = location.function_name( );
	QFileInfo info( source_file );
	auto absoluteFilePath = info.absoluteFilePath( );
	source_file = absoluteFilePath.remove( Cmake_Source_Dir );
}
