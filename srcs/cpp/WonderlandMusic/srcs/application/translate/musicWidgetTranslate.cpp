#include "musicWidgetTranslate.h"

bool MusicWidgetTranslate::init( ) {
	titleName = QObject::tr( "音乐" );
	return true;
}

const QString & MusicWidgetTranslate::getTitleName( ) const {
	return titleName;
}
