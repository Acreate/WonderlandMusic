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
	FavoriteItem *rootItem = nullptr;
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
	virtual size_t filterMusciFromFileVector( std::vector< QString > &result_filter_over, const std::vector< QString > &music_file );
	virtual void loadMusciFromDir( const std::vector< QString > &music_dir );
	virtual bool appendFavorite( const QString &name );

public:
	bool readJsonData( ) override;
	bool writeJsonData( ) override;
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
	virtual FavoriteItem * getRootItem( ) const;
	virtual size_t findMusicItem( MusicItem * &result_item, const QString &find_music ) const;
	virtual size_t findMusicItem( std::vector< MusicItem * > &result_item, const std::vector< QString > &find_music ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual void toMusicIndex( std::vector< size_t > &result_index, const std::vector< MusicItem * > &find_index_music_item );
	virtual void fromMusicIndex( std::vector< MusicItem * > &result_music_item, const std::vector< size_t > &find_index );
	~AppMusicManage( ) override;
	/// @brief 从序列当中移除目标，并不会释放其内存，应当由调用者进行管理
	/// @param target 释放目标
	/// @return 失败返回 false
	virtual bool removeItem( const MusicItem *target );
	/// @brief 从序列当中移除目标，并且释放其内存
	/// @param target 释放目标
	/// @return 失败返回 false
	virtual bool deleteItem( const MusicItem *target );
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
