#include "playerListWidgetMenu.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/playerListWidgetMenuTranslate.h"

#include "../tools/appTranslateTools.h"

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
	loadMusicMenu->setEnabled( enable );
}

bool PlayerListWidgetMenu::init( ) {
	deleteResource( );
	if( AppTranslateTools::getPlayerListWidgetMenu( [this] ( PlayerListWidgetMenuTranslate &translate ) {
		// 加载菜单
		loadMusicMenu = addMenu( translate.getAdd( ) );
		opendSelectFileDialogAction = loadMusicMenu->addAction( translate.getAddMusicFile( ) );
		openSelectDirDialogAction = loadMusicMenu->addAction( translate.getAddMusicDir( ) );
		// 删除菜单
		removeMusicMenu = addMenu( translate.getRemove( ) );
		removeMusicAtList = removeMusicMenu->addAction( translate.getRemoveMusicFile( ) );
		deleteMusicAtDiskFile = removeMusicMenu->addAction( translate.getDeleteMusicFile( ) );
		// 聚合菜单
		aggregateMusicMenu = addMenu( translate.getMove( ) );
		insterPlayAfter = aggregateMusicMenu->addAction( translate.getMoveToPlayerAfter( ) );
		insterPlayBefore = aggregateMusicMenu->addAction( translate.getMoveToPlayerBefore( ) );
		aggregateToSelectFirst = aggregateMusicMenu->addAction( translate.getMoveToSelectFirst( ) );
		aggregateToSelectLast = aggregateMusicMenu->addAction( translate.getMoveToSelectEnd( ) );
		moveTop = aggregateMusicMenu->addAction( translate.getMoveToListFrist( ) );
		moveBottom = aggregateMusicMenu->addAction( translate.getMoveToListEnd( ) );
		// 排序菜单
		sortMusicMenu = addMenu( translate.getSort( ) );
	} ) == false )
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

	connect( openSelectDirDialogAction, &QAction::triggered, this, &PlayerListWidgetMenu::signal_open_dir_dialog );

	connect( moveTop, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_move_top );

	connect( moveBottom, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_move_bottom );

	connect( insterPlayBefore, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_aggregate_play_before );

	connect( insterPlayAfter, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_aggregate_play_after );

	connect( removeMusicAtList, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_music_remove_list );

	connect( deleteMusicAtDiskFile, &QAction::triggered, this, &PlayerListWidgetMenu::signal_select_music_delete_file_list );

	return true;
}
