#include "playerTopWidgetTranslate.h"

#include <QObject>

bool PlayerTopWidgetTranslate::init( ) {
	musicIndex = QObject::tr( "#" );
	musicName = QObject::tr( "歌名" );
	musicSinger = QObject::tr( "歌手" );
	musicDuration = QObject::tr( "时长" );
	return true;
}

const QString & PlayerTopWidgetTranslate::getMusicIndex( ) const {
	return musicIndex;
}

const QString & PlayerTopWidgetTranslate::getMusicName( ) const {
	return musicName;
}

const QString & PlayerTopWidgetTranslate::getMusicSinger( ) const {
	return musicSinger;
}

const QString & PlayerTopWidgetTranslate::getMusicDuration( ) const {
	return musicDuration;
}
