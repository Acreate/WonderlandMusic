#include "playerListMenuTranslate.h"

#include <QObject>

bool PlayerListMenuTranslate::init( ) {
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

	musicTypeName = QObject::tr( "音频类型" );
	anyTypeName = QObject::tr( "所有类型" );

	loadDiskFileTitle = QObject::tr( "加载多个文件" );
	loadDiskDirTitle = QObject::tr( "加载多个目录" );
	return true;
}

const QString & PlayerListMenuTranslate::getLoadDiskFileTitle( ) const {
	return loadDiskFileTitle;
}

const QString & PlayerListMenuTranslate::getLoadDiskDirTitle( ) const {
	return loadDiskDirTitle;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuFileLoadMenu( ) const {
	return playerListMenuFileLoadMenu;
}

const QString & PlayerListMenuTranslate::getPlayerListAddMultiMusicFileToCollectionAction( ) const {
	return playerListAddMultiMusicFileToCollectionAction;
}

const QString & PlayerListMenuTranslate::getPlayerListAddMultiMusicDirToCollectionAction( ) const {
	return playerListAddMultiMusicDirToCollectionAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuenuPlayerMenu( ) const {
	return playerListMenuenuPlayerMenu;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) const {
	return playerListMenuPlayerMenuSetCurrentPlayAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) const {
	return playerListMenuPlayerMenuInsterCurrentPlayAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenu( ) const {
	return playerListMenuControlMenu;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenuRemoveMusicAction( ) const {
	return playerListMenuControlMenuRemoveMusicAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenuDeleteMusicAction( ) const {
	return playerListMenuControlMenuDeleteMusicAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuMoveMenu( ) const {
	return playerListMenuMoveMenu;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenuMoveTopMusicAction( ) const {
	return playerListMenuControlMenuMoveTopMusicAction;
}

const QString & PlayerListMenuTranslate::getPlayerListMenuControlMenuMoveBottomMusicAction( ) const {
	return playerListMenuControlMenuMoveBottomMusicAction;
}

const QString & PlayerListMenuTranslate::getMusicTypeName( ) const {
	return musicTypeName;
}

const QString & PlayerListMenuTranslate::getAnyTypeName( ) const {
	return anyTypeName;
}
