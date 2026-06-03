#include "applications/application.h"

#include "mainWindows/mainWindow.h"

int main( int argc, char *argv[ ], char *envp[ ] ) {
	Application application( argc, argv );
	MainWindow *mainWindow = new MainWindow;
	application.setMainWindowPtr( mainWindow );
	int resultExitCode = application.exec( );
	return resultExitCode;
}
