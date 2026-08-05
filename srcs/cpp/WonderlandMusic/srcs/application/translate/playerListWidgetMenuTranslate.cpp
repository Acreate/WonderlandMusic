#include "playerListWidgetMenuTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( PlayerListWidgetMenu );

bool PlayerListWidgetMenuTranslate::init( ) {
	add = QObject::tr( "添加" );
	addMusicFile = QObject::tr( "添加文件..." );
	addMusicDir = QObject::tr( "添加目录..." );
	remove = QObject::tr( "删除" );
	removeMusicFile = QObject::tr( "从列表中移除" );
	deleteMusicFile = QObject::tr( "从磁盘中移除" );
	move = QObject::tr( "移动" );
	moveToPlayerAfter = QObject::tr( "移动到播放项之前" );
	moveToPlayerBefore = QObject::tr( "移动到播放项之后" );
	moveToSelectFirst = QObject::tr( "移动到首选择项之后" );
	moveToSelectEnd = QObject::tr( "移动到末播放项之前" );
	moveToListFrist = QObject::tr( "移动到列表开始" );
	moveToListEnd = QObject::tr( "移动到列表最后" );
	sort = QObject::tr( "排序" );
	sortName = QObject::tr( "歌名排序" );
	sortTime = QObject::tr( "时长排序" );
	sortSinger = QObject::tr( "歌手排序" );
	return true;
}
const QString & PlayerListWidgetMenuTranslate::getMoveToSelectFirst( ) const {
	return moveToSelectFirst;
}
const QString & PlayerListWidgetMenuTranslate::getMoveToSelectEnd( ) const {
	return moveToSelectEnd;
}
const QString & PlayerListWidgetMenuTranslate::getAdd( ) const {
	return add;
}
const QString & PlayerListWidgetMenuTranslate::getRemove( ) const {
	return remove;
}
const QString & PlayerListWidgetMenuTranslate::getAddMusicFile( ) const {
	return addMusicFile;
}
const QString & PlayerListWidgetMenuTranslate::getAddMusicDir( ) const {
	return addMusicDir;
}
const QString & PlayerListWidgetMenuTranslate::getRemoveMusicFile( ) const {
	return removeMusicFile;
}
const QString & PlayerListWidgetMenuTranslate::getDeleteMusicFile( ) const {
	return deleteMusicFile;
}
const QString & PlayerListWidgetMenuTranslate::getMove( ) const {
	return move;
}
const QString & PlayerListWidgetMenuTranslate::getMoveToPlayerAfter( ) const {
	return moveToPlayerAfter;
}
const QString & PlayerListWidgetMenuTranslate::getMoveToPlayerBefore( ) const {
	return moveToPlayerBefore;
}
const QString & PlayerListWidgetMenuTranslate::getMoveToListFrist( ) const {
	return moveToListFrist;
}
const QString & PlayerListWidgetMenuTranslate::getMoveToListEnd( ) const {
	return moveToListEnd;
}
const QString & PlayerListWidgetMenuTranslate::getSort( ) const {
	return sort;
}
const QString & PlayerListWidgetMenuTranslate::getSortName( ) const {
	return sortName;
}
const QString & PlayerListWidgetMenuTranslate::getSortTime( ) const {
	return sortTime;
}
const QString & PlayerListWidgetMenuTranslate::getSortSinger( ) const {
	return sortSinger;
}
