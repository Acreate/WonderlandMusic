#include "mainWindow.h"

#include "contentWindows/contentWindow.h"

#include "dockWidgets/functionDockWidget.h"
#include "dockWidgets/topToolDockWidget.h"
#include <QMenuBar>

#include "../applications/application.h"
#include "../applications/applicationInstance.h"

#include "dockWidgets/topToolWidget/topToolTitleBarWidget.h"
#include "dockWidgets/topToolWidget/topToolWidget.h"
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
	functionDockWidget->setContextMenuPolicy( Qt::NoContextMenu );
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
}
MainWindow::~MainWindow( ) {

}
size_t MainWindow::triggerTopToolDockEvent( TopToolDockWidget *event_dock_widget, const TopToolDockEventInfo &top_tool_event_info ) {

	auto eventType = top_tool_event_info.getEventType( );
	const TopToolDockEventInfo::TopToolEventData *topToolEventData;
	TopToolEventInfo::Type type;
	switch( eventType ) {
		case TopToolDockEventInfo::EventType::None :
			break;
		case TopToolDockEventInfo::EventType::TopToolEvent :
			topToolEventData = top_tool_event_info.getTopToolEventData( );
			type = topToolEventData->getTopToolEventInfo( )->getType( );
			switch( type ) {
				case TopToolEventInfo::Type::Close :
					ApplicationInstance::getInstance( )->getApplication( )->quit( );
					break;
				case TopToolEventInfo::Type::Min :
					showMinimized( );
					break;
			}
			break;
	}

	return false;
}
