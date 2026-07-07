#include "playerListWidgetMenu.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appMusicManage.h"
#include "../application/appTranslate.h"
#include "../application/appUserInterfaceManage.h"
#include "../application/translate/playerListWidgetMenuTranslate.h"

#include "../scrollArea/musicContreScrollArea.h"

#include "../stackedWidget/mainStackedWidget.h"

#include "../tools/widgetTools.h"

#include "../widget/musicContreWidget.h"

#include "../window/mainWindow.h"
#include "../window/musicListWindow.h"
#include "../window/playerWindow.h"

PlayerListWidgetMenu::PlayerListWidgetMenu( ) : QMenu( ) {
}

PlayerListWidgetMenu::~PlayerListWidgetMenu( ) {
	deleteResource( );
}

bool PlayerListWidgetMenu::deleteResource( ) {
	clear( );
	return true;
}

bool PlayerListWidgetMenu::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	auto appDataManage = appInstance->getAppDataManage( );
	auto appTranslate = appDataManage->getTranslate( );
	if( appTranslate == nullptr )
		return false;
	auto playerListWidgetMenuTranlate = appTranslate->getPlayerListWidgetMenu( );
	if( playerListWidgetMenuTranlate == nullptr )
		return false;
	auto musicDecoder = appInstance->getAppDataManage( )->getAppMusicManage( )->getAppMusicDecoder( );
	if( musicDecoder == nullptr )
		return false;
	auto jsonFileKey = appDataManage->getAppDataJsonKey( );
	if( jsonFileKey == nullptr )
		return false;

	removeMenu = addMenu( playerListWidgetMenuTranlate->getRemoveMenu( ) );
	controlMenu = addMenu( playerListWidgetMenuTranlate->getControlMenu( ) );

	loadMenu = addMenu( playerListWidgetMenuTranlate->getFilePathLoadMenu( ) );

	insterPlayBefore = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getAggregateToPlayerBefore( ) );
	insterPlayAfter = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getAggregateToPlayerAfter( ) );

	moveTop = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getMoveTopAction( ) );
	moveBottom = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getMoveBottomAction( ) );

	aggregateToSelectFirst = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getAggregateToSelectFirst( ) );
	aggregateToSelectLast = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getAggregateToSelectLast( ) );

	removeMusicAtList = removeMenu->QWidget::addAction( playerListWidgetMenuTranlate->getRemoveMusciItemAction( ) );
	deleteMusicAtDiskFile = removeMenu->QWidget::addAction( playerListWidgetMenuTranlate->getDeleteMusicFileAction( ) );

	opendSelectFileDialogAction = loadMenu->addAction( playerListWidgetMenuTranlate->getLoadFileAction( ) );
	oopenSelectDirDialogAction = loadMenu->addAction( playerListWidgetMenuTranlate->getLoadDirAction( ) );

	return true;
}

bool PlayerListWidgetMenu::initBefore( ) {
	deleteResource( );
	return true;
}

bool PlayerListWidgetMenu::initAfter( ) {
	connect( aggregateToSelectFirst, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_aggregate_select_first );

	connect( aggregateToSelectLast, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_aggregate_select_last );

	connect( opendSelectFileDialogAction, &QAction::triggered, this, &PlayerListWidgetMenu::signal_open_file_dialog );

	connect( oopenSelectDirDialogAction, &QAction::triggered, this, &PlayerListWidgetMenu::signal_open_dir_dialog );

	connect( moveTop, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_move_top );

	connect( moveBottom, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_move_bottom );

	connect( insterPlayBefore, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_aggregate_play_before );

	connect( insterPlayAfter, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_aggregate_play_after );

	connect( removeMusicAtList, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_music_remove_list );

	connect( deleteMusicAtDiskFile, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_music_delete_file_list );

	auto musicContreWidget = AppInstance::getAppInstance( )->getAppUserInterfaceManage( )->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( )->getMusicListWindow( )->getMusicContreScrollArea( )->getMusicContreWidget( );
	connect( musicContreWidget, &MusicContreWidget::signal_pop_menu, this, [this]( ) {
		auto pos = QCursor::pos( );
		QPoint suggPos;
		bool menuSuggestionShowMenuPos = WidgetTools::getMenuSuggestionShowMenuPos( suggPos, pos, this );
		if( menuSuggestionShowMenuPos )
			exec( suggPos );
	} );
	return true;
}
