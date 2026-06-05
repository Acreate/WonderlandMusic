#include "mainWindow.h"

#include "contentWindows/contentWindow.h"

#include "dockWidgets/functionDockWidget.h"
#include "dockWidgets/topToolDockWidget.h"
#include <QMenuBar>
MainWindow::Translate::Translate( ) {
	appWindowObjectName = tr( "仙村音乐播放器" );
	windowTitleName = tr( "仙村音乐播放器主窗口" );
}
MainWindow::MainWindow( ) {
	setObjectName( translate.appWindowObjectName );
	setWindowTitle( translate.windowTitleName );
	setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowType::WindowTitleHint );

	contentWindow = new ContentWindow( this );
	contentWindow->setWindowFlags( Qt::WindowType::Widget );
	this->setCentralWidget( contentWindow );

	functionDockWidget = new FunctionDockWidget( this );
	functionDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	functionDockWidget->setAllowedAreas( Qt::DockWidgetArea::LeftDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, functionDockWidget );

	topToolDockWidget = new TopToolDockWidget( this );
	topToolDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	topToolDockWidget->setAllowedAreas( Qt::DockWidgetArea::TopDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, topToolDockWidget );

	this->setDockOptions( QMainWindow::AllowNestedDocks );
	setDocumentMode( true );
}
MainWindow::~MainWindow( ) {

}
