#include "musicWindowTranslate.h"

bool MusicWindowTranslate::init( ) {
	titleName = QObject::tr( "音乐" );
	return true;
}

const QString & MusicWindowTranslate::getTitleName( ) const {
	return titleName;
}
