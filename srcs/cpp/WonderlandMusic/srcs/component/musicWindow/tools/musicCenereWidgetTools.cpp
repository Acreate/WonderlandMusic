#include "musicCenereWidgetTools.h"

#include "../musicCentreWidget/musicCentreWidget.h"
#include "../musicCentreWidget/musicTitleWidget/musicTitleWidget.h"

void MusicCentreWidgetTools::updateMusicCentreWidgetTitleWidthInfo( MusicCentreWidget *music_centre_widget, MusicTitleWidget *music_title_widget ) {
	if( music_centre_widget == nullptr || music_title_widget == nullptr )
		return;
	int intervalWidth;
	int separatorWidth;
	int musicCodeWidth;
	int musicNameWidth;
	int musicSingerNameWidth;
	int musicDurationTimeWidth;
	music_title_widget->getTitleWidthInfo( intervalWidth, separatorWidth, musicCodeWidth, musicNameWidth, musicSingerNameWidth, musicDurationTimeWidth );
	music_centre_widget->updateTitleWidthInfo( music_title_widget, intervalWidth, separatorWidth, musicCodeWidth, musicNameWidth, musicSingerNameWidth, musicDurationTimeWidth );
}
