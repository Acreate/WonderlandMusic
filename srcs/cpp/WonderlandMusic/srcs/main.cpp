#include <QLoggingCategory>
#include <QProcessEnvironment>

#include "applications/applicationInstance.h"

#include "mainWindows/mainWindow.h"
#include <QTextCodec>


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
	} else {
		if( name.indexOf( "usb" ) != -1 ||
			name.indexOf( "driver" ) != -1 )
			category->setEnabled( QtDebugMsg, true );
		else if( oldCategoryFilter )
			oldCategoryFilter( category );
	}

}

int main( int argc, char *argv[ ], char *envp[ ] ) {
	
	oldCategoryFilter = QLoggingCategory::installFilter( myCategoryFilter );

	ApplicationInstance *application = new ApplicationInstance( argc, argv );

	QTextCodec *utf8 = QTextCodec::codecForName( "UTF-8" );
	QTextCodec::setCodecForLocale( utf8 );

	int exec = application->exec( );
	delete application;
	return exec;
}
