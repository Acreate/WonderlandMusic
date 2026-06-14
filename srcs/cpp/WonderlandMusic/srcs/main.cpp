#include <QDateTime>
#include <QLoggingCategory>
#include <QProcessEnvironment>

#include "applications/applicationInstance.h"

#include <QTextCodec>

#include "msgInfo/messageErrorOut.h"

static MessageErrorOut *messageErrorOut = nullptr;
static QLoggingCategory::CategoryFilter oldCategoryFilter = nullptr;

void myCategoryFilter( QLoggingCategory *category ) {

	QString name = category->categoryName( );
	if( name.indexOf( "multimedia" ) != -1 ||
		name.indexOf( "ffmpeg" ) != -1 ||
		name.indexOf( "audio" ) != -1 ||
		name.indexOf( "video" ) != -1 ) {
		category->setEnabled( QtCriticalMsg, false );
		category->setEnabled( QtDebugMsg, false );
		category->setEnabled( QtFatalMsg, false );
		category->setEnabled( QtInfoMsg, false );
		category->setEnabled( QtSystemMsg, false );
		category->setEnabled( QtWarningMsg, false );
		*messageErrorOut << QObject::tr( "屏蔽" ) + "\"" + name + "\"" + QObject::tr( "日志" );
	} else if( name.indexOf( "usb" ) != -1 ||
		name.indexOf( "driver" ) != -1 )
		category->setEnabled( QtDebugMsg, true );
	else if( oldCategoryFilter )
		oldCategoryFilter( category );

}

int main( int argc, char *argv[ ], char *envp[ ] ) {
	messageErrorOut = new MessageErrorOut;
	*messageErrorOut << QObject::tr( "\t: <<<< == 程序日志 == >>>>" );
	messageErrorOut->setJoinString( "\n" );
	oldCategoryFilter = QLoggingCategory::installFilter( myCategoryFilter );
	*messageErrorOut << QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序开始" ) << "----------------------";
	ApplicationInstance application =  ApplicationInstance( argc, argv );

	QTextCodec *utf8 = QTextCodec::codecForName( "UTF-8" );
	QTextCodec::setCodecForLocale( utf8 );

	int exec = application.exec( );
	QString resultString = QObject::tr( "返回值" );
	*messageErrorOut << "----------------------"
		<< QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序结束" )
		<< "\t:\t" + resultString + "{ 0x" + QString::number( exec, 16 ).toUpper( ) + ", "
		+ QString::number( exec ).toUpper( ) + " }";
	delete messageErrorOut;
	return exec;
}
