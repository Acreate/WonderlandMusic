#include "musicTitleWidgetTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( MusicTitleWidget );

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
