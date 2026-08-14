#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class ItemWidthInfo;
class IMusicListMenu;
class MusicLoad;
class FavoriteItem;
class MusicTitleWidget;
class MusicCentreWidget;
class MusicWindow;
class UserMutex;

class MusicListWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicListWidgetTools;

protected:
	UserMutex *userMutex = nullptr;
	MusicCentreWidget *musicCentreWidget;
	FavoriteItem *currentFavoriteItem = nullptr;
	IMusicListMenu *musicListMenu = nullptr;
	QImage *drawBuff = nullptr;
	ItemWidthInfo* itemWidthInfo = nullptr;
public:
	MusicListWidget( MusicCentreWidget *music_centre_widget );
	~MusicListWidget( ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	virtual bool setMusicListMenu( IMusicListMenu *music_list_menu );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual MusicCentreWidget * getMusicCentreWidget( ) const;
	virtual void updateItemWidthInfo( const ItemWidthInfo &item_width_info );
	virtual FavoriteItem * getCurrentFavoriteItem( ) const;
	virtual void setCurrentFavoriteItem( FavoriteItem *favorite_item );
	virtual IMusicListMenu * getMusicListMenu( ) const;
	virtual bool updateMusicListInfo( );
};

#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
