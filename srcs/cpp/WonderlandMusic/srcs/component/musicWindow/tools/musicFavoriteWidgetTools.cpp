#include "MusicFavoriteWidgetTools.h"

#include "../musicCentreWidget/musicFavoriteWidget/musicFavoriteWidget.h"
bool MusicFavoriteWidgetTools::setMusicFavoriteMenu( MusicFavoriteWidget *music_favorite_widget, IMusicFavoriteMenu *music_favorite_menu ) {
	music_favorite_widget->setMusicFavoriteMenu( music_favorite_menu );
	return true;
}
