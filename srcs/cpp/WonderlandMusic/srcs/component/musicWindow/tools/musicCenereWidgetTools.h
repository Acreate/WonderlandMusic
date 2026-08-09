#ifndef MUSICCENEREWIDGETTOOLS_H_H_HEAD__FILE__
#define MUSICCENEREWIDGETTOOLS_H_H_HEAD__FILE__

class MusicTitleWidget;
class MusicCentreWidget;

class MusicCentreWidgetTools {
	friend class MusicTitleWidget;
	static void updateMusicCentreWidgetTitleWidthInfo( MusicCentreWidget *music_centre_widget, MusicTitleWidget *music_title_widget );
};
#endif // MUSICCENEREWIDGETTOOLS_H_H_HEAD__FILE__
