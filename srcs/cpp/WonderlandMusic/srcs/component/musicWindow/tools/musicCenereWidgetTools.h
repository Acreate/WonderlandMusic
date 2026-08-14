#ifndef MUSICCENEREWIDGETTOOLS_H_H_HEAD__FILE__
#define MUSICCENEREWIDGETTOOLS_H_H_HEAD__FILE__
#include "../itemWidthInfo/ItemWidthInfo.h"

class MusicTitleWidget;
class MusicCentreWidget;

class MusicCentreWidgetTools {
	friend class MusicTitleWidget;
	static void updateMusicCentreWidgetTitleWidthInfo( MusicCentreWidget *music_centre_widget, const ItemWidthInfo &item_width_info );
};
#endif // MUSICCENEREWIDGETTOOLS_H_H_HEAD__FILE__
