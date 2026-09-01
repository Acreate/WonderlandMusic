#ifndef IMUSICITEMWIDGET_H_H_HEAD__FILE__
#define IMUSICITEMWIDGET_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicListWidget;
class QMouseEvent;

class IMusicItemWidget : public IMusicCentreWidgetChild {
	friend class IMusicItem;
	friend class IMusicCentreWidget;

protected:
	virtual bool bindMusicItem( IMusicItem *music_item ) = 0;

public:
	IMusicItemWidget( );
	~IMusicItemWidget( ) override;
	virtual bool setMusicListWidget( IMusicListWidget *music_list_widget ) = 0;
	virtual bool updateLayout( ) =0;
	virtual IMusicItem * getBindMusicItem( ) const = 0;
};

#endif // IMUSICITEMWIDGET_H_H_HEAD__FILE__
