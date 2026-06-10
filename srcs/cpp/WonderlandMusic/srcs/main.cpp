#include "applications/applicationInstance.h"

#include "mainWindows/mainWindow.h"
#include <QTextCodec>

int main( int argc, char *argv[ ], char *envp[ ] ) {
	ApplicationInstance *application = new ApplicationInstance( argc, argv );

	//// 关键：让 toLocal8Bit() 输出 GBK（中文Windows默认）
	QTextCodec *utf8 = QTextCodec::codecForName( "UTF-8" );
	QTextCodec::setCodecForLocale( utf8 ); // Qt5有效；Qt6也无害

	int exec = application->exec( );
	delete application;
	return exec;
}
