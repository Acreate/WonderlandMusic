#ifndef MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#define MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class UserMutex;
class MusicLoad;
class FavoriteItem;

class MusicFavoriteWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicCentreWidget;

protected:
	MusicCentreWidget *musicCentreWidget;
	MusicLoad *musicLoad = nullptr;
	UserMutex *userMutex = nullptr;
	std::vector< FavoriteItem * > favoriteItemVector;

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
	virtual bool loadMusicFile( const QString &music_file_path );
	virtual bool loadMusicDir( const QString &music_dir_path );
	virtual MusicLoad * getMusicLoad( ) const;
	virtual bool removeMusicLoad( MusicLoad *music_load );
};

#endif // MUSICFAVORITEWIDGET_H_H_HEAD__FILE__
