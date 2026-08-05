#include "musicWindowTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( MusicWindow );

bool MusicWindowTranslate::init( ) {
	titleName = QObject::tr( "音乐" );
	return true;
}

const QString & MusicWindowTranslate::getTitleName( ) const {
	return titleName;
}
