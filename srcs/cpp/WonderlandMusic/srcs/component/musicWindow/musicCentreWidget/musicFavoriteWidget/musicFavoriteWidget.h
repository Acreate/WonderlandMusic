#ifndef MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#define MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class IMusicFavoriteMenu;
class UserMutex;
class MusicLoad;
class FavoriteItem;
class MusicCentreWidget;

class MusicFavoriteWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	MusicCentreWidget *musicCentreWidget;
	MusicLoad *musicLoad = nullptr;
	UserMutex *userMutex = nullptr;
	std::vector< FavoriteItem * > favoriteItemVector;
	IMusicFavoriteMenu *musicFavoriteMenu;

public:
	MusicFavoriteWidget( MusicCentreWidget *music_centre_widget );
	~MusicFavoriteWidget( ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;

	virtual bool unSafetyClear( );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual int getSuggestWidth( ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual bool removeItem( FavoriteItem *favorite_item );
	virtual MusicLoad * getMusicLoad( ) const;
	virtual bool removeMusicLoad( MusicLoad *music_load );
	virtual bool getIndexFavoriteItem( FavoriteItem *&result_favorite_item, const size_t &index ) const;
	virtual bool getNameFavoriteItem( FavoriteItem *&result_favorite_item, const QString &favorite_item_name ) const;
	virtual MusicCentreWidget * getMusicCentreWidget( ) const;
	virtual IMusicFavoriteMenu * getMusicFavoriteMenu( ) const;
};

#endif // MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
