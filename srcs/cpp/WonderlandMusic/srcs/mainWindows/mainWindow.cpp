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

size_t MainWindow::triggerFunctionDockWidgetEvent( FunctionDockWidget *sender, const FunctionDockWidgetEventInfo &info ) {
	FunctionDockWidgetEventInfo::EventType type = info.getType( );
	switch( type ) {
		case FunctionDockWidgetEventInfo::EventType::Show_Music :
			if( contentWindow->showMusicWidget( ) == false )
				MessageErrorOut( ) << tr( "音乐面板显示失败" );
			break;
		case FunctionDockWidgetEventInfo::EventType::Show_Setting :
			if( contentWindow->showSettingWidget( ) == false )
				MessageErrorOut( ) << tr( "配置面板显示失败" );
			break;
		default :
			MessageErrorOut( ) << tr( "未配置" );
			break;
	}
	return 0;
}
size_t MainWindow::triggerTopToolDockWidgetEvent( TopToolDockWidget *sender, const TopToolDockWidgetEventInfo &info ) {

	TopToolDockWidgetEventInfo::EventType eventType = info.getEventType( );

	const TopToolDockWidgetEventInfo::TopToolEventData *topToolEventData;
	TopToolWidgetEventInfo::Type type;
	const TopToolWidgetEventInfo *topToolEventInfo;
	const QPoint *oldMousePos, *newMousePos;

	switch( eventType ) {
		case TopToolDockWidgetEventInfo::EventType::None :
			break;
		case TopToolDockWidgetEventInfo::EventType::TopToolEvent :
			topToolEventData = info.getTopToolEventData( );
			topToolEventInfo = topToolEventData->getTopToolEventInfo( );
			type = topToolEventInfo->getType( );
			switch( type ) {
				case TopToolWidgetEventInfo::Type::Close :
					ApplicationInstance::getInstance( )->getApplication( )->quit( );
					break;
				case TopToolWidgetEventInfo::Type::Min :
					showMinimized( );
					break;
				case TopToolWidgetEventInfo::Type::MoveTargetOffsetWindow :
					oldMousePos = topToolEventInfo->getOldMousePos( );
					newMousePos = topToolEventInfo->getNewMousePos( );
					move( *newMousePos - *oldMousePos + pos( ) );
					break;
			}
			break;
	}

	return false;
}
