#ifndef IMUSICITEMWIDGET_H_H_HEAD__FILE__
#define IMUSICITEMWIDGET_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class QMouseEvent;

class IMusicItemWidget : public IMusicCentreWidgetChild {
	friend class IMusicItem;

protected:
	virtual bool setBindMusicItem( IMusicItem *music_item ) = 0;

public:
	IMusicItemWidget( );
	~IMusicItemWidget( ) override;
	virtual bool mousePress( const QMouseEvent &mouse_event ) const = 0;
	virtual bool mouseRelease( const QMouseEvent &mouse_event ) const = 0;
	virtual bool drawWidget( ) =0;
	virtual IMusicItem * getBindMusicItem( ) const = 0;
};

#endif // IMUSICITEMWIDGET_H_H_HEAD__FILE__
