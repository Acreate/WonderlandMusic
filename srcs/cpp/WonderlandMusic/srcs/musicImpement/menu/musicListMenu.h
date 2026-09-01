#ifndef MUSICLISTMENU_H_H_HEAD__FILE__
#define MUSICLISTMENU_H_H_HEAD__FILE__
#include <QMenu>

#include <component/musicWindow/interface/menu/iMusicListMenu.h>

class MusicListMenu : public QMenu, public IMusicListMenu {
	Q_OBJECT;

private:
	UserMutex* userMutex = nullptr;
	IMusicCentreWidget *musicCentreWidget = nullptr;

	QAction *playMusicItem = nullptr;
	QAction *removeMusicItem = nullptr;
	QAction *deleteMusicItem = nullptr;
	QAction *moveToTopMusicItem = nullptr;
	QAction *moveToBottomMusicItem = nullptr;
	QAction *moveToPlayTopMusicItem = nullptr;
	QAction *moveToPlayBottomMusicItem = nullptr;

public:
	MusicListMenu( );
	~MusicListMenu( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	IMusicCentreWidget * getMusicCentreWidget( ) const override;

protected:
	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;
	bool execMenu( IMusicListWidget *music_list_widget, IMusicItem *music_item, const QPoint &mouse_global_point ) override;

public:
	QMenu * toMenu( ) override;
};

#endif // MUSICLISTMENU_H_H_HEAD__FILE__
