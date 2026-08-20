#ifndef IMUSICITEMWIDTHINFO_H_H_HEAD__FILE__
#define IMUSICITEMWIDTHINFO_H_H_HEAD__FILE__

#include <interface/iAppJsonData.h>

#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicTitleWidget;

class IMusicItemWidthInfo : public IMusicCentreWidgetChild, public IAppJsonData {
public:
	IMusicItemWidthInfo( );

	virtual int getSuggestHeight( ) const = 0;
	virtual int getClickWidth( ) const = 0;
	virtual int getCalculateMinWidth( ) const = 0;
	virtual int getIntervalWidth( ) const = 0;
	virtual int getSeparatorWidth( ) const = 0;
	virtual int getMusicCodeWidth( ) const = 0;
	virtual int getMusicNameWidth( ) const = 0;
	virtual int getMusicSingerNameWidth( ) const = 0;
	virtual int getMusicDurationTimeWidth( ) const = 0;
	virtual int getMinItemWidth( ) const = 0;
	virtual bool setIMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) = 0;
	virtual bool updateInfo( ) = 0;
	virtual IMusicTitleWidget * setMusicTitleWidget( IMusicTitleWidget *music_title_widget ) = 0;
	virtual IMusicTitleWidget * getMusicTitleWidget( ) = 0;
};

#endif // IMUSICITEMWIDTHINFO_H_H_HEAD__FILE__
