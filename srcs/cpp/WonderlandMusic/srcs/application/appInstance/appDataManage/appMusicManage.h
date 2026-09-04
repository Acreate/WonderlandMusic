#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__

#include <interface/iAppCore.h>
#include <interface/iAppJsonData.h>

#include <component/musicWindow/interface/info/iMusicDataManage.h>

#include <interface/iAppResourceCore.h>
class MusicFavoriteItem;
class MusicItemWidthInfo;
class IMusicFavoriteItem;
class IMusicItemWidthInfo;

class IMusicItem;
class QPainter;
class UserMutex;

class AppMusicManage : public QObject, public IMusicDataManage, public IAppJsonData, public IAppResourceCore {
	Q_OBJECT;

protected:
	UserMutex *userMutex = nullptr;
	MusicItemWidthInfo *musicItemWidthInfo = nullptr;
	std::vector< MusicFavoriteItem * > musicFavoriteItemVector;
	MusicFavoriteItem *currenstFavoriteItem = nullptr;
	MusicFavoriteItem *defaultFavoriteItem = nullptr;
	IMusicCentreWidget *musicCentreWidget = nullptr;
	std::vector< QString > supperDecodeFileSuffix;

protected:
	bool deleteResource( ) override;
	virtual bool unsafeClearMusicFavoriteItem( );

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;

protected:
	virtual bool unsafeClear( );

public:
	virtual bool getMusicWindowInfoJsonData( QJsonObject &result_json_object );
	virtual bool setMusicWindowInfoJsonData( const QJsonObject &result_json_object );
	virtual IMusicItemWidthInfo * getMusicItemWidthInfo( ) const;
	virtual bool setMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info );
	virtual bool musicFileNameSupperDecoder( const QString &file_name ) const;
	virtual const std::vector< QString > & getSupperDecodeFileSuffix( ) const;

private:
	virtual bool unsafeGetMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const;
	virtual bool unsafeGetMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const;
	virtual bool unsafeGetMusicFavoriteItem( std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const;

protected:
	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;

	bool setCurrentSelectFavoriteItem( IMusicFavoriteItem *set_select_music_favorite_item ) override;

public:
	IMusicCentreWidget * getMusicCentreWidget( ) const override;
	bool initDefaultMusicFavoriteItem( ) override;
	bool clear( ) override;
	bool getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const override;
	bool getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const override;
	bool getMusicFavoriteItem( std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const override;
	bool getCurrentSelectFavoriteItem( IMusicFavoriteItem *&result_current_select_music_favorite_item ) const override;
};
#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
