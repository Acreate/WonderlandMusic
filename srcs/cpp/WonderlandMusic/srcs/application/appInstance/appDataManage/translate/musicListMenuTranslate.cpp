#include "musicListMenuTranslate.h"

bool MusicListMenuTranslate::init( ) {
	playMusicItem = QObject::tr( "播放选择项" );
	removeMusicItem = QObject::tr( "移除选择项" );
	deleteMusicItem = QObject::tr( "删除选择项" );
	moveToTopMusicItem = QObject::tr( "移动选择项到列表顶部" );
	moveToBottomMusicItem = QObject::tr( "移动选择项到列表底部" );
	moveToPlayTopMusicItem = QObject::tr( "移动选择项到播放之前" );
	moveToPlayBottomMusicItem = QObject::tr( "移动选择项到播放之后" );
	return true;
}
const QString & MusicListMenuTranslate::getPlayMusicItem( ) const {
	return playMusicItem;
}
const QString & MusicListMenuTranslate::getRemoveMusicItem( ) const {
	return removeMusicItem;
}
const QString & MusicListMenuTranslate::getDeleteMusicItem( ) const {
	return deleteMusicItem;
}
const QString & MusicListMenuTranslate::getMoveToTopMusicItem( ) const {
	return moveToTopMusicItem;
}
const QString & MusicListMenuTranslate::getMoveToBottomMusicItem( ) const {
	return moveToBottomMusicItem;
}
const QString & MusicListMenuTranslate::getMoveToPlayTopMusicItem( ) const {
	return moveToPlayTopMusicItem;
}
const QString & MusicListMenuTranslate::getMoveToPlayBottomMusicItem( ) const {
	return moveToPlayBottomMusicItem;
}
