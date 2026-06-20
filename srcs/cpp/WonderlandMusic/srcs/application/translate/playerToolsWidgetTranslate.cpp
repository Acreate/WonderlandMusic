#include "playerToolsWidgetTranslate.h"

#include <QObject>

bool PlayerToolsWidgetTranslate::init( ) {
	thePreviousSong = QObject::tr( "上一曲" );
	controlPlay = QObject::tr( "播放" );
	controlPausa = QObject::tr( "暂停" );
	theNextSong = QObject::tr( "下一曲" );
	currentPlayList = QObject::tr( "当前播放列表" );
	playSongDateTimeSpace = QObject::tr( "/" );
	return true;
}

const QString & PlayerToolsWidgetTranslate::getThePreviousSong( ) const {
	return thePreviousSong;
}

const QString & PlayerToolsWidgetTranslate::getControlPlay( ) const {
	return controlPlay;
}

const QString & PlayerToolsWidgetTranslate::getControlPausa( ) const {
	return controlPausa;
}

const QString & PlayerToolsWidgetTranslate::getTheNextSong( ) const {
	return theNextSong;
}

const QString & PlayerToolsWidgetTranslate::getCurrentPlayList( ) const {
	return currentPlayList;
}

const QString & PlayerToolsWidgetTranslate::getPlaySongDateTimeSpace( ) const {
	return playSongDateTimeSpace;
}
