#ifndef MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/musicWindow/interface/ItemWidget/iMusicFavoriteItemWidget.h>

class MusicFavoriteItemWidget : public QWidget, public IMusicFavoriteItemWidget {
	Q_OBJECT;

private:
	IMusicCentreWidget *musicCentreWidget = nullptr;
	IMusicFavoriteItem *musicFavoriteItem = nullptr;
	IMusicFavoriteWidget *musicFavoriteWidget = nullptr;
	QLabel *nameLabel = nullptr;

public:
	MusicFavoriteItemWidget( );
	~MusicFavoriteItemWidget( ) override;

protected:

public:
	IMusicCentreWidget * getMusicCentreWidget( ) const override;
	bool updateLayout( ) override;
	bool setMusicFavoriteWidget( IMusicFavoriteWidget *music_favorite_widget ) override;

	bool bindMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) override;

	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;

public:
	IMusicFavoriteItem * getBindMusicFavoriteItem( ) const override;
	bool setPos( const int &target_pos_x, const int &target_pos_y ) override;
	bool setSize( const int &set_width, const int &set_height ) override;
	bool getPos( int &target_pos_x, int &target_pos_y ) const override;
	bool getSize( int &result_width, int &result_height ) const override;
	bool showItemWidget( ) override;
	bool hideItemWidget( ) override;
};

#endif // MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
