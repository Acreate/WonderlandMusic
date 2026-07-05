#include "playerListWidgetMenuTranlate.h"

bool PlayerListWidgetMenuTranlate::init( ) {
	filePathLoadMenu = QObject::tr( "加载菜单" );
	loadFileAction = QObject::tr( "添加文件到列表" );
	loadDirAction = QObject::tr( "添加目录到列表" );

	playerMusicMenu = QObject::tr( "播放菜单" );
	aggregateToPlayerBefore = QObject::tr( "聚合到播放项之前" );
	aggregateToPlayerAfter = QObject::tr( "聚合到播放项之后" );

	removeMenu = QObject::tr( "删除菜单" );
	removeMusciItemAction = QObject::tr( "从列表移除" );
	deleteMusicFileAction = QObject::tr( "从文件移除" );

	controlMenu = QObject::tr( "控制菜单" );
	moveTopAction = QObject::tr( "选中列表移动到顶部" );
	moveBottomAction = QObject::tr( "选中列表移动到底部" );
	aggregateToSelectFirst = QObject::tr( "聚合到首选项" );
	aggregateToSelectLast = QObject::tr( "聚合到末选项" );
	return true;
}

const QString & PlayerListWidgetMenuTranlate::getFilePathLoadMenu( ) const {
	return filePathLoadMenu;
}

const QString & PlayerListWidgetMenuTranlate::getLoadFileAction( ) const {
	return loadFileAction;
}

const QString & PlayerListWidgetMenuTranlate::getLoadDirAction( ) const {
	return loadDirAction;
}

const QString & PlayerListWidgetMenuTranlate::getPlayerMusicMenu( ) const {
	return playerMusicMenu;
}

const QString & PlayerListWidgetMenuTranlate::getAggregateToPlayerAfter( ) const {
	return aggregateToPlayerAfter;
}

const QString & PlayerListWidgetMenuTranlate::getAggregateToPlayerBefore( ) const {
	return aggregateToPlayerBefore;
}

const QString & PlayerListWidgetMenuTranlate::getControlMenu( ) const {
	return controlMenu;
}

const QString & PlayerListWidgetMenuTranlate::getRemoveMusciItemAction( ) const {
	return removeMusciItemAction;
}

const QString & PlayerListWidgetMenuTranlate::getDeleteMusicFileAction( ) const {
	return deleteMusicFileAction;
}

const QString & PlayerListWidgetMenuTranlate::getRemoveMenu( ) const {
	return removeMenu;
}

const QString & PlayerListWidgetMenuTranlate::getMoveTopAction( ) const {
	return moveTopAction;
}

const QString & PlayerListWidgetMenuTranlate::getMoveBottomAction( ) const {
	return moveBottomAction;
}

const QString & PlayerListWidgetMenuTranlate::getAggregateToSelectFirst( ) const {
	return aggregateToSelectFirst;
}

const QString & PlayerListWidgetMenuTranlate::getAggregateToSelectLast( ) const {
	return aggregateToSelectLast;
}
