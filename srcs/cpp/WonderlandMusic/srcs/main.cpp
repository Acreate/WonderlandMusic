#include <QDateTime>
#include <QLoggingCategory>
#include <qfile.h>

#include "application/appEventManage.h"
#include "application/appInstance.h"
#include "application/appUserInterfaceManage.h"

#include "msgInfo/messageErrorOut.h"

#include "tools/pathTools.h"

static MessageErrorOut *messageErrorOut = nullptr;
static MessageString *permit = nullptr;
static MessageString *screening = nullptr;
static QLoggingCategory::CategoryFilter oldCategoryFilter = nullptr;

#ifdef CANCEL_FILTER
	#define is_en_filter 0
#else
	#define is_en_filter 1
#endif

#ifdef CANCEL_WRITE_LOG
	#define is_en_write_log 0
#else
	#define is_en_write_log 1
#endif

#if is_en_write_log
#include "tools/templateArgs.h"
	#define new_ptr( ptr ) TemplateArgs::make_ptr( ptr )
#else
	#define new_ptr( ptr ) ( ptr = nullptr)
#endif

#if is_en_filter
	#define en_filter() 
#else
	#define en_filter() return
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
		if( messageErrorOut )
			*screening << QObject::tr( "屏蔽" ) + "\"" + name + "\"" + QObject::tr( "日志" );
	} else {
		if( name.indexOf( "usb" ) != -1 ||
			name.indexOf( "driver" ) != -1 )
			category->setEnabled( QtDebugMsg, true );
		else if( oldCategoryFilter )
			oldCategoryFilter( category );
		if( messageErrorOut )
			*permit << QObject::tr( "通过" ) + "\"" + name + "\"" + QObject::tr( "日志" );
	}
}

int main( int argc, char *argv[ ], char *envp[ ] ) {
	messageErrorOut = new_ptr( messageErrorOut );
	permit = new_ptr( permit );
	screening = new_ptr( screening );
	if( messageErrorOut ) {
		*messageErrorOut << QObject::tr( "\t: <<<< == 程序日志 == >>>>" );
		messageErrorOut->setJoinString( "\n" );
		*messageErrorOut << QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序开始" ) << "----------------------";
	}
	oldCategoryFilter = QLoggingCategory::installFilter( myCategoryFilter );

	AppInstance *application = new AppInstance( argc, argv );

	QString resultString = QObject::tr( "返回值" );
	if( application->init( ) == false ) {
		if( messageErrorOut ) {
			*messageErrorOut << "----------------------"
				<< QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序结束" )
				<< "\t:\t" + resultString + "{ 0x" + QString::number( -1, 16 ).toUpper( ) + ", "
				+ QString::number( -1 ).toUpper( ) + " }";
			delete messageErrorOut;
		}
		return -1;
	}
	int exec = -1;
	if( application->getAppUserInterfaceManage( )->showMainWindow( ) )
		exec = application->getAppEventManage( )->exec( );
	if( messageErrorOut ) {
		permit->setJion( "\n" );
		screening->setJion( "\n" );
		*messageErrorOut << *permit;
		*messageErrorOut << "";
		*messageErrorOut << *screening;
		*messageErrorOut << "----------------------"
			<< QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序结束" )
			<< "\t:\t" + resultString + "{ 0x" + QString::number( exec, 16 ).toUpper( ) + ", "
			+ QString::number( exec ).toUpper( ) + " }";
		delete messageErrorOut;
		messageErrorOut = nullptr;
	}
	delete application;
	return exec;
}
