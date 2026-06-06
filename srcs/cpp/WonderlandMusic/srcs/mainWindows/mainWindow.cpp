#include "mainWindow.h"

#include "contentWindows/contentWindow.h"

#include "dockWidgets/functionDockWidget.h"
#include "dockWidgets/topToolDockWidget.h"
#include <QMenuBar>
#include <qboxlayout.h>

#include "../applications/application.h"
#include "../applications/applicationInstance.h"

#include "dockWidgets/topToolWidget/topToolTitleBarWidget.h"
#include "dockWidgets/topToolWidget/topToolWidget.h"

MainWindow::Translate::Translate( ) {
	appWindowObjectName = tr( "仙村音乐播放器" );
	windowTitleName = tr( "仙村音乐播放器主窗口" );
}
MainWindow::MainWindow( ) {
	scaleStatus = ScaleStatus::None;
	scalePermission = false;
	checkScaleMargin = 5;
	setObjectName( translate.appWindowObjectName );
	setWindowTitle( translate.windowTitleName );
	setWindowFlags( Qt::WindowType::ToolTip );

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
void MainWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
	auto rect = contentsRect( );
	currenWidth = rect.width( ) - rect.x( );
	currentHeight = rect.height( ) - rect.y( );
}
void MainWindow::enterEvent( QEnterEvent *event ) {
	QMainWindow::enterEvent( event );
	scalePermission = true;
}
void MainWindow::leaveEvent( QEvent *event ) {
	QMainWindow::leaveEvent( event );
	scalePermission = false;
}
void MainWindow::mouseMoveEvent( QMouseEvent *event ) {
	QMainWindow::mouseMoveEvent( event );
	if( scalePermission ) {
		// todo : 开始缩放
		auto rect = contentsRect( );
		auto newWidth = rect.width( ) - rect.x( );
		auto newHeight = rect.height( ) - rect.y( );
	}

}
void MainWindow::mousePressEvent( QMouseEvent *event ) {
	QMainWindow::mousePressEvent( event );
	if( scalePermission ) {
		// todo : 检测缩放位置
	}
}
void MainWindow::mouseReleaseEvent( QMouseEvent *event ) {
	QMainWindow::mouseReleaseEvent( event );
	scalePermission = false;
	scaleStatus = ScaleStatus::None;
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
