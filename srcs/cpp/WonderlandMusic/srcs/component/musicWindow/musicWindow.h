#ifndef MUSICWINDOW_H_H_HEAD__FILE__
#define MUSICWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../../component/optionWindow/interface/optionPanel.h"

#include "../../interface/iAppJsonData.h"
#include "../../interface/iAppResourceCore.h"

class IMusicItemWidthInfo;
class IMusicWidgetSizeInfo;
class IMusicFavoriteWidget;
class IMusicTitleWidget;
class IMusicListWidget;
class IMusicListMenu;
class IMusicFavoriteMenu;
class MusicCentreWidget;
class UserMutex;

class MusicWindow : public QMainWindow, public OptionPanel, public IAppJsonData, public IAppResourceCore {
	Q_OBJECT;
	friend class MusicItem;

private:
	UserMutex *userMutex = nullptr;
	MusicCentreWidget *musicCentreWidget = nullptr;

public:
	MusicWindow( );
	~MusicWindow( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	QWidget * toWidget( ) override;
	virtual MusicCentreWidget * getMusicCentreWidget( ) const;
	bool showPanelBefore( ) override;
	bool hidePanelBefore( ) override;
	bool releasePanelBefore( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	QString getTypeName( ) const override;
	virtual IMusicFavoriteWidget * getMusicFavoriteWidget( ) const;
	virtual IMusicListWidget * getMusicListWidget( ) const;
	virtual IMusicTitleWidget * getMusicTitleWidget( ) const;
	virtual IMusicFavoriteMenu * getMusicFavoriteMenu( ) const;
	virtual IMusicListMenu * getMusicListMenu( ) const;
	virtual IMusicWidgetSizeInfo * getMusicWidgetSizeInfo( ) const;
	virtual IMusicFavoriteWidget * setMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget );
	virtual IMusicListWidget * setMusicListWidget( IMusicListWidget *const music_list_widget );
	virtual IMusicTitleWidget * setMusicTitleWidget( IMusicTitleWidget *const music_title_widget );
	virtual IMusicFavoriteMenu * setMusicFavoriteMenu( IMusicFavoriteMenu *music_favorite_menu );
	virtual IMusicListMenu * setMusicListMenu( IMusicListMenu *music_list_menu );

	virtual IMusicWidgetSizeInfo * setMusicWidgetSizeInfo( IMusicWidgetSizeInfo *const music_widget_size_info );
	virtual IMusicItemWidthInfo * setMusicItemWidthInfo( IMusicItemWidthInfo *const music_item_width_info );
};

#endif // MUSICWINDOW_H_H_HEAD__FILE__
