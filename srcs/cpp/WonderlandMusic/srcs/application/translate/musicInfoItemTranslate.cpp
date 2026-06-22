#include "musicInfoItemTranslate.h"

#include <QObject>

bool MusicInfoItemTranslate::init( ) {
	musichumanBeingNameNone = QObject::tr( "匿名" );
	return true;
}

const QString & MusicInfoItemTranslate::getMusichumanBeingNameNone( ) const {
	return musichumanBeingNameNone;
}
