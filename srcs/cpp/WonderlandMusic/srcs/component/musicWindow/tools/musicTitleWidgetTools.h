#ifndef MUSICTITLEWIDGETTOOLS_H_H_HEAD__FILE__
#define MUSICTITLEWIDGETTOOLS_H_H_HEAD__FILE__
class MusicCentreWidget;
class MusicTitleWidget;

class MusicTitleWidgetTools {
private:
	friend class MusicCentreWidget;
	static void updateMusicTitleWidgetTitleWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );
};
#endif // MUSICTITLEWIDGETTOOLS_H_H_HEAD__FILE__
