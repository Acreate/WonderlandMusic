#ifndef MUSICCENTREWIDGET_H_H_HEAD__FILE__
#define MUSICCENTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class IMusicTitleWidget;
class IMusicListWidget;
class IMusicFavoriteWidget;
class IMusicListMenu;
class IMusicFavoriteMenu;
class TransparencyScrollBar;
class QScrollArea;
class UserMutex;
class MusicWindow;

class MusicCentreWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicCentreWidgetTools;

private:
	MusicWindow *musicWindow;
	UserMutex *userMutex = nullptr;
	QScrollArea *musicfavoriteWidgetScrollArea = nullptr;
	QScrollArea *musicTitleWidgetScrollArea = nullptr;
	QScrollArea *musicListWidgetScrollArea = nullptr;
	IMusicFavoriteWidget *musicFavoriteWidget = nullptr;
	IMusicListWidget *musicListWidget = nullptr;
	IMusicTitleWidget *musicTitleWidget = nullptr;
	IMusicFavoriteMenu *musicFavoriteMenu = nullptr;
	IMusicListMenu *musicListMenu = nullptr;

public:
	MusicCentreWidget( MusicWindow *parent );
	~MusicCentreWidget( ) override;

protected:
	bool deleteResource( ) override;
	void resizeEvent( QResizeEvent *event ) override;
	virtual QScrollArea * createControlScrollArea( );

public:
	bool calculateSize( );
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual MusicWindow * getMusicWindow( ) const;
	virtual IMusicFavoriteWidget * getMusicFavoriteWidget( ) const;
	virtual IMusicListWidget * getMusicListWidget( ) const;
	virtual IMusicTitleWidget * getMusicTitleWidget( ) const;
	virtual IMusicFavoriteMenu * getMusicFavoriteMenu( ) const;
	virtual IMusicListMenu * getMusicListMenu( ) const;
	virtual IMusicFavoriteWidget * setMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget );
	virtual IMusicListWidget * setMusicListWidget( IMusicListWidget *const music_list_widget );
	virtual IMusicTitleWidget * setMusicTitleWidget( IMusicTitleWidget *const music_title_widget );
	virtual IMusicFavoriteMenu * setMusicFavoriteMenu( IMusicFavoriteMenu *music_favorite_menu );
	virtual IMusicListMenu * setMusicListMenu( IMusicListMenu *music_list_menu );
};

#endif // MUSICCENTREWIDGET_H_H_HEAD__FILE__
