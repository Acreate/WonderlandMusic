#include "MusicFavoriteWidgetTools.h"

#include "../musicCentreWidget/musicFavoriteWidget/musicFavoriteWidget.h"
bool MusicFavoriteWidgetTools::setMusicFavoriteMenu( MusicFavoriteWidget *music_favorite_widget, IMusicFavoriteMenu *music_favorite_menu ) {
	if( music_favorite_widget == nullptr )
		return false;
	music_favorite_widget->setMusicFavoriteMenu( music_favorite_menu );
	return true;
}
