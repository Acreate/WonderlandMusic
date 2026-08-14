#include "MusicListWidgetTools.h"

#include "../musicCentreWidget/musicListWidget/musicListWidget.h"

void MusicListWidgetTools::updateItemWidthInfo( MusicListWidget *targetr, const ItemWidthInfo &item_width_info ) {
	targetr->updateItemWidthInfo( item_width_info );
}
bool MusicListWidgetTools::setMusicListMenu( MusicListWidget *targetr, IMusicListMenu *music_list_menu ) {
	targetr->setMusicListMenu( music_list_menu );
	return true;
}
