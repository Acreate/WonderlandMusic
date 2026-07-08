#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__
#include "../interface/iAppCore.h"
#include "../interface/iAppDiskJsonData.h"
class FavoriteItem;
class FavoriteWidget;
class FavoriteItemWidget;
class MusicContreWidget;
class LabelWidget;
class MusicItem;
class UserMutex;
class QMediaPlayer;
class AppMusicDecoder;

class AppMusicManage : public QObject, public IAppCore, public IAppDiskJsonData {
	Q_OBJECT;

private Q_SLOTS:
	void deleteFavoriteItem( QObject *delete_ptr );
	void deleteMusicItem( QObject *delete_ptr );

protected:
	UserMutex *loadMutex = nullptr;
	AppMusicDecoder *appMusicDecoder = nullptr;
	std::vector< QMediaPlayer * > loadMediaVector;
	std::vector< QString > loadFileVector;
	size_t loadCount;
	std::vector< MusicItem * > musicItemVector;
	std::vector< FavoriteItem * > favoriteItemVector;
	MusicContreWidget *musicContreWidget = nullptr;
	FavoriteWidget *favoriteWidget = nullptr;
	QString openMultipleFilePath;
	QString openMultipleDirPath;

protected:
	bool deleteResource( ) override;
	virtual bool connectPlayerListWidgetMenuSignal( );
	virtual bool connectFavoriteWidgetMenuSignal( );
	virtual void loadFile( const QString &music_file );
	virtual void loadMusciFromFileVector( const std::vector< QString > &music_file );
	virtual void loadMusciFromDir( const std::vector< QString > &music_dir );
	virtual bool appendFavorite( const QString &name );
	virtual bool appendFirstFavorite( );

public:
	bool readJsonData( ) override;
	bool writeJsonData( ) override;
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
	virtual bool getRootFavoriteItem( FavoriteItem *&result_root_item ) const;
	virtual size_t findMusicItem( MusicItem * &result_item, const QString &find_music ) const;
	virtual size_t findMusicItem( std::vector< MusicItem * > &result_item, const std::vector< QString > &find_music ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual void toMusicIndex( std::vector< size_t > &result_index, const std::vector< MusicItem * > &find_index_music_item );
	virtual void fromMusicIndex( std::vector< MusicItem * > &result_music_item, const std::vector< size_t > &find_index );
	~AppMusicManage( ) override;
	virtual AppMusicDecoder * getAppMusicDecoder( ) const;
	virtual bool removeSelectMusicItem( );
	virtual bool deleteSelectMusicItem( );
	virtual bool openSelectMusicFileDialog( );
	virtual bool openSelectMusicDirDialog( );
	virtual bool selectMusicItemMoveToTop( );
	virtual bool selectMusicItemMoveToBottom( );
	virtual bool selectMusicItemAggregateToSelectFirst( );
	virtual bool selectMusicItemAggregateToSelectLast( );
	virtual bool selectMusicItemAggregateToPlayItemBefore( );
	virtual bool selectMusicItemAggregateToPlayItemAfter( );
	virtual bool selectFavorite( );
Q_SIGNALS:
	void signal_update_favorite_item( const FavoriteItemWidget *favorite_widget );
};
#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
