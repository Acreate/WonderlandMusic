#include "mainWindow.h"

#include "contentWindows/contentWindow.h"

#include "dockWidgets/functionDockWidget.h"
#include "dockWidgets/topToolDockWidget.h"
#include "../applications/application.h"
#include "../applications/applicationInstance.h"

#include "dockWidgets/topToolWidget/topToolTitleBarWidget.h"
#include "dockWidgets/topToolWidget/topToolWidget.h"

#include <QMouseEvent>

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
}
MainWindow::~MainWindow( ) {

}
size_t MainWindow::triggerFunctionDockEvent( FunctionDockWidget *event_dock_widget, const FunctionDockEventInfo &function_dock_event_info ) {
	switch( function_dock_event_info.getType( ) ) {

		case FunctionDockEventInfo::EventType::Show_Music :
			MessageErrorOut( ) << tr( "显示音乐面板" );
			break;
		case FunctionDockEventInfo::EventType::Show_Setting :
			MessageErrorOut( ) << tr( "显示配置面板" );
			break;
		default :
			MessageErrorOut( ) << tr( "未配置" );
			break;
	}
	return 0;
}
size_t MainWindow::triggerTopToolDockEvent( TopToolDockWidget *event_dock_widget, const TopToolDockEventInfo &top_tool_event_info ) {

	auto eventType = top_tool_event_info.getEventType( );
	const TopToolDockEventInfo::TopToolEventData *topToolEventData;
	TopToolEventInfo::Type type;
	const TopToolEventInfo *topToolEventInfo;
	const QPoint *oldMousePos, *newMousePos;

	switch( eventType ) {
		case TopToolDockEventInfo::EventType::None :
			break;
		case TopToolDockEventInfo::EventType::TopToolEvent :
			topToolEventData = top_tool_event_info.getTopToolEventData( );
			topToolEventInfo = topToolEventData->getTopToolEventInfo( );
			type = topToolEventInfo->getType( );
			switch( type ) {
				case TopToolEventInfo::Type::Close :
					ApplicationInstance::getInstance( )->getApplication( )->quit( );
					break;
				case TopToolEventInfo::Type::Min :
					showMinimized( );
					break;
				case TopToolEventInfo::Type::MoveTargetOffsetWindow :
					oldMousePos = topToolEventInfo->getOldMousePos( );
					newMousePos = topToolEventInfo->getNewMousePos( );
					move( *newMousePos - *oldMousePos + pos( ) );
					break;
			}
			break;
	}

	return false;
}
