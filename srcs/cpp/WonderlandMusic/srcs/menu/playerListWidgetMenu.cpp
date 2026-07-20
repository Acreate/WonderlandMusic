#include "playerListWidgetMenu.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"

PlayerListWidgetMenu::PlayerListWidgetMenu( ) : QMenu( ) {
}

PlayerListWidgetMenu::~PlayerListWidgetMenu( ) {
	deleteResource( );
}

bool PlayerListWidgetMenu::deleteResource( ) {
	clear( );
	return true;
}

FavoriteItem * PlayerListWidgetMenu::getSelectItem( ) const {
	return selectItem;
}

void PlayerListWidgetMenu::setSelectItem( FavoriteItem *const select_item ) {
	selectItem = select_item;
	bool enable = select_item == nullptr;
	loadMenu->setEnabled( enable );
}

bool PlayerListWidgetMenu::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	auto appDataManage = appInstance->getAppDataManage( );
	auto appTranslate = appDataManage->getTranslate( );
	if( appTranslate == nullptr )
		return false;

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

	return true;
}
