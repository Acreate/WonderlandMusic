#include "music.h"
Music::Music( const QString &music_path, QObject *const parent ) : QObject( parent ),
	musicPath( music_path ) { }
