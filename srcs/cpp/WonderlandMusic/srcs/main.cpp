#include <qloggingcategory.h>

#include "applications/applicationInstance.h"

#include "mainWindows/mainWindow.h"


int main( int argc, char *argv[ ], char *envp[ ] ) {
	ApplicationInstance *application = new ApplicationInstance( argc, argv );
	
	int exec = application->exec( );
	delete application;
	return exec;
}
