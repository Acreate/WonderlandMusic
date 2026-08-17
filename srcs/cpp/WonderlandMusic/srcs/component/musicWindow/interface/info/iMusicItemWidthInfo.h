#ifndef IMUSICITEMWIDTHINFO_H_H_HEAD__FILE__
#define IMUSICITEMWIDTHINFO_H_H_HEAD__FILE__

#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicItemWidthInfo : public IMusicCentreWidgetChild {
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
};

#endif // IMUSICITEMWIDTHINFO_H_H_HEAD__FILE__
