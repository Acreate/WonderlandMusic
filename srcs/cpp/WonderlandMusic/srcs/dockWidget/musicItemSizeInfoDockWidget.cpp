#include "musicItemSizeInfoDockWidget.h"

#include <QScrollBar>

#include "../application/appInstance.h"
#include "../application/appUserInterfaceManage.h"

#include "../scrollArea/musicContreScrollArea.h"

#include "../stackedWidget/mainStackedWidget.h"

#include "../widget/playerListTopWidget.h"

#include "../window/mainWindow.h"
#include "../window/musicListWindow.h"
#include "../window/playerWindow.h"

MusicItemSizeInfoDockWidget::MusicItemSizeInfoDockWidget( QMainWindow *main_window ) : QDockWidget( main_window ), mainWindow( main_window ) {
}

MusicItemSizeInfoDockWidget::~MusicItemSizeInfoDockWidget( ) {
	deleteResource( );
}

bool MusicItemSizeInfoDockWidget::deleteResource( ) {
	mainWindow->removeDockWidget( this );
	Delete_Resource_App_Core_Ptr( titleBarWidget );
	Delete_Resource_App_Core_Ptr( playerListTopWidget );
	Delete_Resource_App_Core_Ptr( playerListTopWidgetScrollArea );
	return true;
}

bool MusicItemSizeInfoDockWidget::getJsonData( QJsonObject &get_json_object ) const {
	playerListTopWidget->getJsonData( get_json_object );
	return true;
}

bool MusicItemSizeInfoDockWidget::setJsonData( const QJsonObject &set_json_object ) {
	playerListTopWidget->setJsonData( set_json_object );
	return true;
}

bool MusicItemSizeInfoDockWidget::init( ) {
	Before_Init_Resource_App_Core_Ptr( playerListTopWidget );
	Init_Resource_App_Core_Ptr( playerListTopWidget );
	After_Init_Resource_App_Core_Ptr( playerListTopWidget );
	return true;
}

bool MusicItemSizeInfoDockWidget::initBefore( ) {
	deleteResource( );

	playerListTopWidgetScrollArea = new QScrollArea( this );
	playerListTopWidget = new PlayerListTopWidget( playerListTopWidgetScrollArea );
	titleBarWidget = new QWidget( this );
	playerListTopWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	playerListTopWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playerListTopWidgetScrollArea->setWidgetResizable( true );
	playerListTopWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );
	playerListTopWidgetScrollArea->verticalScrollBar( )->setEnabled( false );
	setAllowedAreas( Qt::TopDockWidgetArea );
	setContentsMargins( 0, 0, 0, 0 );
	return true;
}

bool MusicItemSizeInfoDockWidget::initAfter( ) {
	playerListTopWidgetScrollArea->setWidget( playerListTopWidget );
	setTitleBarWidget( titleBarWidget );
	setWidget( playerListTopWidgetScrollArea );
	setFixedHeight( playerListTopWidget->height( ) );
	mainWindow->addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, this );

	auto scrollBar = playerListTopWidgetScrollArea->horizontalScrollBar( );
	auto uiManage = AppInstance::getAppInstance( )->getAppUserInterfaceManage( );
	auto listContre = uiManage->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( )->getMusicListWindow( )->getMusicContreScrollArea( );
	connect( listContre, &MusicContreScrollArea::signal_horizontal_scroll_set_value, scrollBar, &QScrollBar::setValue );

	return true;
}

QScrollArea * MusicItemSizeInfoDockWidget::getPlayerListTopWidgetScrollArea( ) const {
	return playerListTopWidgetScrollArea;
}

PlayerListTopWidget * MusicItemSizeInfoDockWidget::getPlayerListTopWidget( ) const {
	return playerListTopWidget;
}

QWidget * MusicItemSizeInfoDockWidget::getTitleBarWidget( ) const {
	return titleBarWidget;
}
