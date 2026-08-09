#include "MusicListWidgetTools.h"

#include "../musicCentreWidget/musicListWidget/musicListWidget.h"

void MusicListWidgetTools::updateItemWidthInfo( MusicListWidget *targetr, MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width ) {
	if( targetr == nullptr )
		return;
	targetr->updateItemWidthInfo( music_title_widget, interval_width, separator_width, music_code_width, music_name_width, music_singer_name_width, music_duration_time_width );
}
void MusicListWidgetTools::setMenu( MusicListWidget *targetr, IMusicListMenu *music_list_menu ) {
	if( targetr == nullptr )
		return;
	targetr->setMusicListMenu( music_list_menu );
}
