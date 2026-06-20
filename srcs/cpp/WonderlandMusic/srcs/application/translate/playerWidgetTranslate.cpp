#include "playerWidgetTranslate.h"

#include <QObject>

bool PlayerWidgetTranslate::init( ) {
	playMusic = QObject::tr( "开始" );
	stopMusic = QObject::tr( "停止" );
	pauseMusic = QObject::tr( "暂停" );
	playListWidget = QObject::tr( "播放列表" );

	return true;
}

const QString & PlayerWidgetTranslate::getPlayMusic( ) const {
	return playMusic;
}

const QString & PlayerWidgetTranslate::getStopMusic( ) const {
	return stopMusic;
}

const QString & PlayerWidgetTranslate::getPauseMusic( ) const {
	return pauseMusic;
}

const QString & PlayerWidgetTranslate::getPlayListWidget( ) const {
	return playListWidget;
}
