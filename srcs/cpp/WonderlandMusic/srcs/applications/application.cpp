#include "application.h"

#include "../mainWindows/mainWindow.h"
Application::Application( int &argc, char **const argv, const int i ) : QApplication( argc, argv, i ) {
	mainWindowPtr = nullptr;
	firstShow = false;
}
Application::~Application( ) { }
bool Application::notify( QObject *object, QEvent *event ) {
	switch( event->type( ) ) {
		case QEvent::Show :
			if( mainWindowPtr == object && firstShow == false ) {
				firstMainWindowShow( mainWindowPtr );
				firstShow = true;
			}
			break;
		case QEvent::Close :
			// 主窗口关闭，则退出软件
			if( mainWindowPtr == object )
				quit( );
			break;
		case QEvent::Quit :
			mainWindowPtr->deleteLater( );
			mainWindowPtr = nullptr;
			break;
	}
	return QApplication::notify( object, event );
}
void Application::setMainWindowPtr( MainWindow *main_window_ptr ) {
	if( main_window_ptr == nullptr )
		return;
	MainWindow *oldMainWindow = mainWindowPtr;
	mainWindowPtr = main_window_ptr;
	if( oldMainWindow ) {
		oldMainWindow->hide( );
		oldMainWindow->deleteLater( );
	}
	firstShow = false;
	main_window_ptr->show( );

}
void Application::firstMainWindowShow( MainWindow *first_show_main_window ) {

}
