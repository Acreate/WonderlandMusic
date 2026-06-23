#include <QDateTime>
#include <QProcessEnvironment>
#include <qfile.h>

#include "application/appInstance.h"

#include "msgInfo/messageErrorOut.h"

#include "tools/autoMakePtrTools.h"

#include "window/mainWindow.h"

static MessageErrorOut *messageErrorOut = nullptr;
static QLoggingCategory::CategoryFilter oldCategoryFilter = nullptr;

#define is_en_filter 0

#if is_en_filter
	#define en_filter() return
#else
	#define en_filter()
#endif
void myCategoryFilter( QLoggingCategory *category ) {
	QString name = category->categoryName( );
	if( name == "qt.multimedia.ffmpeg" || name == "qt.multimedia.ffmpeg.metadata" || name == "qt.multimedia.audiodevice.probes" || name == "qt.multimedia.ffmpeg.mediadataholder" ) {
		en_filter( );

		category->setEnabled( QtCriticalMsg, false );
		category->setEnabled( QtDebugMsg, false );
		category->setEnabled( QtFatalMsg, false );
		category->setEnabled( QtInfoMsg, false );
		category->setEnabled( QtSystemMsg, false );
		category->setEnabled( QtWarningMsg, false );
		*messageErrorOut << QObject::tr( "屏蔽" ) + "\"" + name + "\"" + QObject::tr( "日志" );
	} else {
		if( name.indexOf( "usb" ) != -1 ||
			name.indexOf( "driver" ) != -1 )
			category->setEnabled( QtDebugMsg, true );
		else if( oldCategoryFilter )
			oldCategoryFilter( category );
		*messageErrorOut << QObject::tr( "通过" ) + "\"" + name + "\"" + QObject::tr( "日志" );
	}
}

int main( int argc, char *argv[ ], char *envp[ ] ) {
	messageErrorOut = new MessageErrorOut;
	*messageErrorOut << QObject::tr( "\t: <<<< == 程序日志 == >>>>" );
	messageErrorOut->setJoinString( "\n" );
	oldCategoryFilter = QLoggingCategory::installFilter( myCategoryFilter );
	*messageErrorOut << QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序开始" ) << "----------------------";

	AppInstance application( argc, argv );
	QString resultString = QObject::tr( "返回值" );
	if( application.init( ) == false ) {
		*messageErrorOut << "----------------------"
			<< QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序结束" )
			<< "\t:\t" + resultString + "{ 0x" + QString::number( -1, 16 ).toUpper( ) + ", "
			+ QString::number( -1 ).toUpper( ) + " }";
		delete messageErrorOut;
		return -1;
	}

	int exec = application.run( );
	*messageErrorOut << "----------------------"
		<< QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序结束" )
		<< "\t:\t" + resultString + "{ 0x" + QString::number( exec, 16 ).toUpper( ) + ", "
		+ QString::number( exec ).toUpper( ) + " }";
	delete messageErrorOut;
	return exec;
}
