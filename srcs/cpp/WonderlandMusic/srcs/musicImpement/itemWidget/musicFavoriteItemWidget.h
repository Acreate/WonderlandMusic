#ifndef MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/musicWindow/interface/ItemWidget/iMusicFavoriteItemWidget.h>

class MusicFavoriteItemWidget : public QWidget, public IMusicFavoriteItemWidget {
	Q_OBJECT;

private:
	MusicCentreWidget *musicCentreWidget = nullptr;
	IMusicFavoriteItem* musicFavoriteItem = nullptr;
	IMusicFavoriteWidget* musicFavoriteWidget = nullptr;
public:
	MusicFavoriteItemWidget( );
	~MusicFavoriteItemWidget( ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	bool updateLayout( ) override;

protected:
	bool setBindMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) override;

public:
	IMusicFavoriteItem * getBindMusicFavoriteItem( ) const override;

protected:
	bool setMusicFavoriteWidget( IMusicFavoriteWidget *music_favorite_widget ) override;

public:
	QImage * getDrawBuff( ) override;
	IMusicFavoriteWidget * getMusicFavoriteWidget( ) const override;
};

#endif // MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
