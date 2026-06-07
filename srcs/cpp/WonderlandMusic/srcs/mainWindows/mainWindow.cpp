#include "mainWindow.h"

#include "contentWindows/contentWindow.h"

#include "dockWidgets/functionDockWidget.h"
#include "dockWidgets/topToolDockWidget.h"

#include "dockWidgets/topToolWidget/topToolTitleBarWidget.h"
#include "dockWidgets/topToolWidget/topToolWidget.h"

#include <QMouseEvent>

#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"

#include "../msgInfo/messageErrorOut.h"

#include "dockWidgets/functionWidget/functionWidgetBarWidget.h"

MainWindow::Translate::Translate( ) {
	appWindowObjectName = tr( "仙村音乐播放器" );
	windowTitleName = tr( "仙村音乐播放器主窗口" );
}
MainWindow::MainWindow( ) {
	setObjectName( translate.appWindowObjectName );
	setWindowTitle( translate.windowTitleName );
	QFlags< Qt::WindowType > flags = Qt::WindowType::Window | Qt::WindowType::CustomizeWindowHint;
	setWindowFlags( flags );

	contentWindow = new ContentWindow( this );
	contentWindow->setWindowFlags( Qt::WindowType::Widget );
	this->setCentralWidget( contentWindow );

	functionDockWidget = new FunctionDockWidget( this );
	functionDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	functionDockWidget->setAllowedAreas( Qt::DockWidgetArea::LeftDockWidgetArea );
	functionDockWidget->setContextMenuPolicy( Qt::NoContextMenu );
	functionDockWidget->setTitleBarWidget( new FunctionWidgetBarWidget( functionDockWidget ) );
	addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, functionDockWidget );

	topToolDockWidget = new TopToolDockWidget( this );
	topToolDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	topToolDockWidget->setAllowedAreas( Qt::DockWidgetArea::TopDockWidgetArea );
	topToolDockWidget->setContextMenuPolicy( Qt::NoContextMenu );
	topToolDockWidget->setTitleBarWidget( new TopToolTitleBarWidget( topToolDockWidget ) );
	addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, topToolDockWidget );

	this->setDockOptions( QMainWindow::AllowNestedDocks );
	setDocumentMode( true );
	setContextMenuPolicy( Qt::NoContextMenu );

	application = ApplicationInstance::getApplicationInstance( );
	applicationEvenTrigger = application->getApplicationEvenTrigger( );

	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerTopToolWidgetEvent, [this] ( auto, const TopToolWidgetEventInfo &info ) {
		auto type = info.getType( );
		switch( type ) {
			case TopToolWidgetEventInfo::Type::Close :
				close( );
				break;
			case TopToolWidgetEventInfo::Type::Min :
				showMinimized( );
				break;
			case TopToolWidgetEventInfo::Type::MoveTargetOffsetWindow : {
				const QPoint *oldMousePos = info.getOldMousePos( );
				const QPoint *newMousePos = info.getNewMousePos( );
				QPoint thisPos = pos( );
				move( *newMousePos - *oldMousePos + thisPos );
			}
			break;
		}
	} );
}
MainWindow::~MainWindow( ) {

}
