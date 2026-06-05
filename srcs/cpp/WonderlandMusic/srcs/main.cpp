#include "applications/application.h"

#include "mainWindows/mainWindow.h"

int main( int argc, char *argv[ ], char *envp[ ] ) {
	Application *application = new Application( argc, argv );
	int exec = application->exec( );
	delete application;
	return exec;
}
