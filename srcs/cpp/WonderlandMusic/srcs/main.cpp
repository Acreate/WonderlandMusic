#include "applications/application.h"

#include "mainWindows/mainWindow.h"

int main( int argc, char *argv[ ], char *envp[ ] ) {
	Application application( argc, argv );
	application.setMainWindowPtr( new MainWindow );
	return application.exec( );
}
