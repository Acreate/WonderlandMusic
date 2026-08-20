#include "musicTitleWidgetTranslate.h"

bool MusicTitleWidgetTranslate::init( ) {
	musicCode = QObject::tr( "编号" );
	musicName = QObject::tr( "歌名" );
	musicSingeName = QObject::tr( "歌手" );
	musicDurationTime = QObject::tr( "时长" );
	return true;
}
const QString & MusicTitleWidgetTranslate::getMusicCode( ) const {
	return musicCode;
}
const QString & MusicTitleWidgetTranslate::getMusicName( ) const {
	return musicName;
}
const QString & MusicTitleWidgetTranslate::getMusicSingeName( ) const {
	return musicSingeName;
}
const QString & MusicTitleWidgetTranslate::getMusicDurationTime( ) const {
	return musicDurationTime;
}
