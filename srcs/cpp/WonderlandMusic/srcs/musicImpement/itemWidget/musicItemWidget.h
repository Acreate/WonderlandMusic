#ifndef MUSICITEMWIDGET_H_H_HEAD__FILE__
#define MUSICITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <component/musicWindow/interface/ItemWidget/iMusicItemWidget.h>

class MusicItemWidget : public QWidget, public IMusicItemWidget {
	Q_OBJECT;

private:
	IMusicCentreWidget *musicCentreWidget = nullptr;
	IMusicItem *musicItem = nullptr;
	IMusicListWidget *musicListWidget = nullptr;
	QLabel *idLabel = nullptr;
	QLabel *nameLabel = nullptr;
	QLabel *singerLabel = nullptr;
	QLabel *elapsedTimeLabel = nullptr;

public:
	MusicItemWidget( );
	~MusicItemWidget( ) override;

protected:
	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;

public:
	IMusicCentreWidget * getMusicCentreWidget( ) const override;
	bool updateLayout( ) override;
	bool setMusicListWidget( IMusicListWidget *music_list_widget ) override;

protected:
	bool bindMusicItem( IMusicItem *music_item ) override;
	void paintEvent( QPaintEvent *event ) override;

public:
	IMusicItem * getBindMusicItem( ) const override;
	QWidget * toWidget( ) override;
};

#endif // MUSICITEMWIDGET_H_H_HEAD__FILE__
