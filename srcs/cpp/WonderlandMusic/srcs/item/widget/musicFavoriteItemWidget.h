#ifndef MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/musicWindow/interface/ItemWidget/iMusicFavoriteItemWidget.h>

class MusicFavoriteItemWidget : public QWidget, public IMusicFavoriteItemWidget {
	Q_OBJECT;

private:
	MusicCentreWidget *musicCentreWidget = nullptr;

public:
	MusicFavoriteItemWidget( );
	~MusicFavoriteItemWidget( ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	bool mousePress( const QMouseEvent &mouse_event ) const override;
	bool mouseRelease( const QMouseEvent &mouse_event ) const override;
	bool drawWidget( ) override;
};

#endif // MUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
