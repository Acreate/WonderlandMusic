#include "mainWindow.h"

#include "dockWidgets/functionDockWidget.h"
#include "dockWidgets/topToolDockWidget.h"

#include <QMouseEvent>

#include "contentWindow.h"

#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"

#include "../msgInfo/messageErrorOut.h"

#include "../widgets/topToolWidget.h"

MainWindow::Translate::Translate( ) {
	appWindowObjectName = tr( "仙村音乐播放器" );
	windowTitleName = tr( "仙村音乐播放器主窗口" );
}
MainWindow::MainWindow( ) : BaseMainWindow( nullptr ) {

	setObjectName( translate.appWindowObjectName );
	setWindowTitle( translate.windowTitleName );
	QFlags< Qt::WindowType > flags = Qt::WindowType::Window | Qt::WindowType::CustomizeWindowHint;
	setWindowFlags( flags );

	contentWindow = new ContentWindow( this );
	this->setCentralWidget( contentWindow );

	functionDockWidget = new FunctionDockWidget( this );
	functionDockWidget->setAllowedAreas( Qt::DockWidgetArea::LeftDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, functionDockWidget );

	topToolDockWidget = new TopToolDockWidget( this );
	topToolDockWidget->setAllowedAreas( Qt::DockWidgetArea::TopDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, topToolDockWidget );

	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
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
