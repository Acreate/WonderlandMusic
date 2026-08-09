#ifndef MUSICLISTWIDGETTOOLS_H_H_HEAD__FILE__
#define MUSICLISTWIDGETTOOLS_H_H_HEAD__FILE__

class IMusicListMenu;
class MusicTitleWidget;
class MusicListWidget;

class MusicListWidgetTools {
private:
	friend class MusicCentreWidget;
	static void updateItemWidthInfo( MusicListWidget *targetr, MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );
	static void setMenu( MusicListWidget *targetr, IMusicListMenu *music_list_menu );
};

#endif // MUSICLISTWIDGETTOOLS_H_H_HEAD__FILE__
