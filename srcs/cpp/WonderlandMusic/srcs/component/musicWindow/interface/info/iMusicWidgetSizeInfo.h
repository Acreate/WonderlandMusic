#ifndef IMUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
#define IMUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
#include <interface/iAppJsonData.h>

#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicWidgetSizeInfo : public IMusicCentreWidgetChild, public IAppJsonData {
	friend class IMusicCentreWidget;

protected:
	virtual int setFavoriteWidth( const int &favoriet_width ) = 0;
	virtual int setTitleHeight( const int &favoriet_width ) = 0;

public:
	IMusicWidgetSizeInfo( );
	virtual int getFavoriteWidth( ) const = 0;
	virtual int getTitleHeight( ) const = 0;
	virtual bool updateMusicWidgetLayout( ) =0;
};

#endif // IMUSICWIDGETSIZEINFO_H_H_HEAD__FILE__
