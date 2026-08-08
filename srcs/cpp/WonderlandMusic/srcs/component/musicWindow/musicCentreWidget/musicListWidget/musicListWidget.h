#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

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
	MusicLoad *musicLoad = nullptr;
	FavoriteItem *currentFavoriteItem = nullptr;
	std::vector< FavoriteItem * > favoriteItemVector;

public:
	MusicListWidget( MusicCentreWidget *music_centre_widget );
	~MusicListWidget( ) override;

protected:
	bool deleteResource( ) override;
	void paintEvent( QPaintEvent *event ) override;
	virtual bool unSafetyClear( );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual MusicCentreWidget * getMusicCentreWidget( ) const;
	virtual void updateItemWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );
	virtual bool removeItem( FavoriteItem *favorite_item );
	virtual void clear( );
	virtual FavoriteItem * getCurrentFavoriteItem( ) const;
	virtual bool loadMusicFile( const QString &music_file_path );
	virtual bool loadMusicDir( const QString &music_dir_path );
	virtual MusicLoad * getMusicLoad( ) const;
	virtual bool removeMusicLoad( MusicLoad *music_load );
};

class MusicListWidgetTools {
private:
	friend class MusicCentreWidget;
	static void updateItemWidthInfo( MusicListWidget *targetr, MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );
};

#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
