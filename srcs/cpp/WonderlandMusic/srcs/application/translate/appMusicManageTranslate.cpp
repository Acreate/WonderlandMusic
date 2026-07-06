#include "appMusicManageTranslate.h"

bool AppMusicManageTranslate::init( ) {
	rootFavoriteName = QObject::tr( "默认" );
	return true;
}

const QString & AppMusicManageTranslate::getRootFavoriteName( ) const {
	return rootFavoriteName;
}
