#include <QApplication>
#include <QPushButton>

int main( int argc, char *argv[ ], char *envp[ ] ) {
	QApplication application( argc, argv );
	QPushButton *qPushButton = new QPushButton;
	qPushButton->setText( QObject::tr( "你好" ) );
	qPushButton->show( );
	QObject::connect( qPushButton, &QPushButton::clicked, [&application]( ) {
		application.quit( );
	} );
	int resultExitCode = application.exec( );
	delete qPushButton;
	return resultExitCode;
}
