#include <QLoggingCategory>
#include "application/appInstance.h"
#include "dateTimeFormat/dateTimeFormat.h"
#include "head/result_message_out.h"

#include "msgInfo/messageErrorOut.h"
#include "msgInfo/messageString.h"
#include "tools/pathTools.h"
static MessageErrorOut *messageErrorOut = nullptr;
static MessageString *permit = nullptr;
static MessageString *screening = nullptr;
static QLoggingCategory::CategoryFilter oldCategoryFilter = nullptr;
static QDateTime *startDateTime = nullptr;
static QDateTime *endDateTime = nullptr;
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
	#define new_ptr( ptr ) TemplateArgs::make_args_ptr( ptr )
#else
	#define new_ptr( ptr ) ( ptr = nullptr)
#endif
#if is_en_filter
	#define en_filter() 
#else
	#define en_filter() return
#endif
static void myCategoryFilter( QLoggingCategory *category ) {
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

static void initTimeInfo( ) {
	messageErrorOut = new_ptr( messageErrorOut );
	permit = new_ptr( permit );
	screening = new_ptr( screening );
	startDateTime = new_ptr( startDateTime );
	endDateTime = new_ptr( endDateTime );
}
static void satrtProcess( ) {
	if( messageErrorOut ) {
		*startDateTime = QDateTime::currentDateTime( );
		*messageErrorOut << QObject::tr( "\t: <<<< == 程序日志 == >>>>" );
		messageErrorOut->setJoinString( "\n" );
		*messageErrorOut << startDateTime->toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序开始" ) << "----------------------";
	}
}

static int endProcess( int exit_code ) {
	if( messageErrorOut ) {
		permit->setJion( "\n" );
		screening->setJion( "\n" );
		*messageErrorOut << *permit;
		*messageErrorOut << "";
		*messageErrorOut << *screening;

		*endDateTime = QDateTime::currentDateTime( );
		auto milliseconds = *endDateTime - *startDateTime;
		QString runSepTime = DateTimeFormat::millsecondToHourMinSecFrom( milliseconds.count( ) ) + QObject::tr( " -> 运行周期" );

		QString resultString = QObject::tr( "返回值" );
		*messageErrorOut << "----------------------"
			<< QDateTime::currentDateTime( ).toString( "\t:\tyyyy年MM月dd日 hh:mm:ss.z -> " ) + QObject::tr( "程序结束" ) << "\t:\t" + runSepTime
			<< "\t:\t" + resultString + "{ 0x" + QString::number( exit_code, 16 ).toUpper( ) + ", "
			+ QString::number( exit_code ).toUpper( ) + " }";

		delete messageErrorOut;
		delete permit;
		delete screening;
		delete startDateTime;
		delete endDateTime;

		messageErrorOut = nullptr;
		permit = nullptr;
		screening = nullptr;
		startDateTime = nullptr;
		endDateTime = nullptr;
	}
	return exit_code;
}

int main( int argc, char *argv[ ], char *envp[ ] ) {
	int exec;
	initTimeInfo( );

	oldCategoryFilter = QLoggingCategory::installFilter( myCategoryFilter );
	satrtProcess( );
	AppInstance *application = new AppInstance( argc, argv );

	if( application->initBefore( ) == false ) {
		exec = -1;
		Result_Var_Function_Messag_Ptr_Out_Args( exec, application, initBefore, QObject::tr( "预备初始化失败" ) );
		exec = endProcess( exec );
		delete application;
		return exec;
	}

	if( application->init( ) == false ) {
		exec = -2;
		Result_Var_Function_Messag_Ptr_Out_Args( exec, application, init, QObject::tr( "初始化失败" ) );

		exec = endProcess( exec );
		delete application;
		return exec;
	}

	if( application->initAfter( ) == false ) {
		exec = -3;
		Result_Var_Function_Messag_Ptr_Out_Args( exec, application, initAfter, QObject::tr( "后置初始化失败" ) );
		exec = endProcess( exec );
		delete application;
		return exec;
	}

	exec = application->exec( );
	exec = endProcess( exec );

	delete application;
	return exec;
}
