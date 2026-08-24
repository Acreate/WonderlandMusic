#ifndef MUSICITEMWIDGET_H_H_HEAD__FILE__
#define MUSICITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../../component/musicWindow/interface/ItemWidget/iMusicItemWidget.h"

class MusicItemWidget : public QWidget, public IMusicItemWidget {
	Q_OBJECT;

private:
	MusicCentreWidget *musicCentreWidget = nullptr;
	IMusicItem* musicItem = nullptr;
public:
	MusicItemWidget( );
	~MusicItemWidget( ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	bool mousePress( const QMouseEvent &mouse_event ) const override;
	bool mouseRelease( const QMouseEvent &mouse_event ) const override;
	bool drawWidget( ) override;

protected:
	bool setBindMusicItem( IMusicItem *music_item ) override;

public:
	IMusicItem * getBindMusicItem( ) const override;
};

#endif // MUSICITEMWIDGET_H_H_HEAD__FILE__
