#ifndef MUSICITEMWIDGET_H_H_HEAD__FILE__
#define MUSICITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/musicWindow/interface/ItemWidget/iMusicItemWidget.h>

#include "../../interface/iAppRenderBuff.h"

class MusicItemWidget : public QWidget, public IMusicItemWidget, public IAppRenderBuff {
	Q_OBJECT;

private:
	IMusicCentreWidget *musicCentreWidget = nullptr;
	IMusicItem *musicItem = nullptr;
	IMusicListWidget *musicListWidget = nullptr;

public:
	MusicItemWidget( );
	~MusicItemWidget( ) override;
	bool renderToBuff( ) override;

	IMusicCentreWidget * getMusicCentreWidget( ) const override;
	bool updateLayout( ) override;
	bool setMusicListWidget( IMusicListWidget *music_list_widget ) override;

	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;
	bool bindMusicItem( IMusicItem *music_item ) override;

protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;

public:
	IMusicItem * getBindMusicItem( ) const override;
	QWidget * toWidget( ) override;
};

#endif // MUSICITEMWIDGET_H_H_HEAD__FILE__
