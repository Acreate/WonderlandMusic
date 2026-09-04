#ifndef IMUSICITEMWIDGET_H_H_HEAD__FILE__
#define IMUSICITEMWIDGET_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicItem;
class IMusicListWidget;
class QMouseEvent;

class IMusicItemWidget : public IMusicCentreWidgetChild {
protected:
	~IMusicItemWidget( ) override;

public:
	IMusicItemWidget( );
	virtual bool bindMusicItem( IMusicItem *music_item ) = 0;
	virtual bool setMusicListWidget( IMusicListWidget *music_list_widget ) = 0;
	virtual bool updateLayout( ) =0;
	virtual IMusicItem * getBindMusicItem( ) const = 0;
	virtual QWidget * toWidget( ) =0;
};

#endif // IMUSICITEMWIDGET_H_H_HEAD__FILE__
