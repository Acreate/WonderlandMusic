#include "playerListWidgetMenuTranlate.h"

bool PlayerListWidgetMenuTranlate::init( ) {
	playerListMenuFileLoadMenu = QObject::tr( "加载菜单" );
	playerListAddMultiMusicFileToCollectionAction = QObject::tr( "添加文件到列表" );
	playerListAddMultiMusicDirToCollectionAction = QObject::tr( "添加目录到列表" );

	playerListMenuenuPlayerMenu = QObject::tr( "播放菜单" );
	playerListMenuPlayerMenuSetCurrentPlayAction = QObject::tr( "从选中开始播放" );
	playerListMenuPlayerMenuInsterCurrentPlayAction = QObject::tr( "插入选中并播放" );

	playerListMenuMoveMenu = QObject::tr( "删除菜单" );
	playerListMenuControlMenuRemoveMusicAction = QObject::tr( "从列表移除" );
	playerListMenuControlMenuDeleteMusicAction = QObject::tr( "从文件移除" );

	playerListMenuControlMenu = QObject::tr( "控制菜单" );
	playerListMenuControlMenuMoveTopMusicAction = QObject::tr( "选中列表移动到顶部" );
	playerListMenuControlMenuMoveBottomMusicAction = QObject::tr( "选中列表移动到底部" );

	return true;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuFileLoadMenu( ) const {
	return playerListMenuFileLoadMenu;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListAddMultiMusicFileToCollectionAction( ) const {
	return playerListAddMultiMusicFileToCollectionAction;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListAddMultiMusicDirToCollectionAction( ) const {
	return playerListAddMultiMusicDirToCollectionAction;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuenuPlayerMenu( ) const {
	return playerListMenuenuPlayerMenu;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) const {
	return playerListMenuPlayerMenuSetCurrentPlayAction;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) const {
	return playerListMenuPlayerMenuInsterCurrentPlayAction;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuControlMenu( ) const {
	return playerListMenuControlMenu;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuControlMenuRemoveMusicAction( ) const {
	return playerListMenuControlMenuRemoveMusicAction;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuControlMenuDeleteMusicAction( ) const {
	return playerListMenuControlMenuDeleteMusicAction;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuMoveMenu( ) const {
	return playerListMenuMoveMenu;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuControlMenuMoveTopMusicAction( ) const {
	return playerListMenuControlMenuMoveTopMusicAction;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerListMenuControlMenuMoveBottomMusicAction( ) const {
	return playerListMenuControlMenuMoveBottomMusicAction;
}
