#include "contentWindow.h"

#include <QPainter>

#include "../mainWindow.h"

#include "contentWidgetConpoment/findDockWidget.h"
#include "contentWidgetConpoment/playerDockWidget.h"

#include "coreWindow/coreWindow.h"

ContentWindow::ContentWindow( MainWindow *parent ) : QMainWindow( parent ), mainWindow( parent ) {

	Qt::DockWidgetArea dockWidgetArea;

	findDockWidget = new FindDockWidget( this );
	dockWidgetArea = Qt::DockWidgetArea::TopDockWidgetArea;
	findDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	findDockWidget->setAllowedAreas( dockWidgetArea );
	addDockWidget( dockWidgetArea, findDockWidget );

	playerDockWidget = new PlayerDockWidget( this );
	dockWidgetArea = Qt::DockWidgetArea::BottomDockWidgetArea;
	playerDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	playerDockWidget->setAllowedAreas( dockWidgetArea );
	addDockWidget( dockWidgetArea, playerDockWidget );

	coreWindow = new CoreWindow( this );
	coreWindow->setWindowFlags( Qt::WindowType::Widget );
	setCentralWidget( coreWindow );
}
bool ContentWindow::showMusicWidget( ) {
	return coreWindow->showMusicWidget( );
}
bool ContentWindow::showSettingWidget( ) {
	return coreWindow->showSettingWidget( );
}
size_t ContentWindow::triggerFindDockWidgetEvent( FindDockWidget *sender, const FindDockWidgetEventInfo &info ) {

	return 0;
}
size_t ContentWindow::triggerPlayerDockWidgetEvent( PlayerDockWidget *sender, const PlayerDockWidgetEventInfo &info ) {
	auto eventType = info.getEventType( );
	switch( eventType ) {

		case PlayerDockWidgetEventInfo::EventType::None :
			return ContentWindowEvent::triggerContentWindowEvent( mainWindow, this, ContentWindowEventInfo( ContentWindowEventInfo::EventType::None ) );
		case PlayerDockWidgetEventInfo::EventType::Player :
			return ContentWindowEvent::triggerContentWindowEvent( mainWindow, this, ContentWindowEventInfo( ContentWindowEventInfo::EventType::Player ) );
		case PlayerDockWidgetEventInfo::EventType::Pause :
			return ContentWindowEvent::triggerContentWindowEvent( mainWindow, this, ContentWindowEventInfo( ContentWindowEventInfo::EventType::Pause ) );
		case PlayerDockWidgetEventInfo::EventType::Next_Track :
			return ContentWindowEvent::triggerContentWindowEvent( mainWindow, this, ContentWindowEventInfo( ContentWindowEventInfo::EventType::Next_Track ) );
		case PlayerDockWidgetEventInfo::EventType::Previous_Track :
			return ContentWindowEvent::triggerContentWindowEvent( mainWindow, this, ContentWindowEventInfo( ContentWindowEventInfo::EventType::Previous_Track ) );
	}
	return 0;
}
size_t ContentWindow::triggerCoreWindowEvent( CoreWindow *sender, const CoreWindowEventInfo &info ) {
	return 0;
}
