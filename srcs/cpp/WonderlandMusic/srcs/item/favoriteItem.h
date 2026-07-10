#ifndef FAVORITEITEM_H_H_HEAD__FILE__
#define FAVORITEITEM_H_H_HEAD__FILE__
#include "../interface/iAppJsonData.h"
class AppMusicManage;
class FavoriteItemWidget;
class MusicItem;

class FavoriteItem : public QObject, public IAppJsonData {
	Q_OBJECT;

public:
	class ItemInfo;

	class ItemInfo {
		friend class FavoriteItem;
		QString name;
		std::vector< MusicItem * > musicItemvVector;
		FavoriteItemWidget *favoriteItemWidget;
		QObject *deleteErrorObj;
		bool read = true;
		ItemInfo( const QString &name, const std::vector< MusicItem * > &music_itemv_vector, FavoriteItemWidget *favorite_item_widget );

	public:
		virtual ~ItemInfo( );
	};

protected:
	ItemInfo *info;

public:
	FavoriteItem( const QString &name, const std::vector< MusicItem * > &music_itemv_vector );
	virtual void setEnabled( bool enabled );

	FavoriteItem( const QString &name ) : FavoriteItem( name, std::vector< MusicItem * >( ) ) {
	}

	~FavoriteItem( ) override;
	bool eventFilter( QObject *watched, QEvent *event ) override;
	virtual void setFavoriteName( const QString &favorite_name );
	virtual QString getFavoriteName( ) const;
	virtual FavoriteItemWidget * getFavoriteItemWidget( ) const;

public:
	static bool getJsonDataVector( QJsonObject &get_json_object, const std::vector< FavoriteItem * > &conver_vector );
	static bool setJsonDataVector( std::vector< FavoriteItem * > &result_vector, const QJsonObject &set_json_object );

public:
	virtual ItemInfo * getInfo( ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual const QString & getName( ) const;
	virtual const std::vector< MusicItem * > & getMusicItemvVector( ) const;
	virtual bool appendMusicItem( MusicItem *music_item );
	virtual bool appendMusicItem( const std::vector< MusicItem * > &append_item_vector );
	virtual bool appendMusicItem( const QString &music_item );
	virtual bool appendMusicItem( const std::vector< QString > &append_item_vector );
	virtual bool removeMusicItem( const MusicItem *music_item );
	virtual bool removeMusicItem( const std::vector< MusicItem * > &remove_item_vector );
	virtual bool removeMusicItem( const QString &music_item );
	virtual bool removeMusicItem( const std::vector< QString > &remove_item_vector );
	virtual std::vector< MusicItem * > findMusicName( const QString &find_name ) const;
	virtual std::vector< MusicItem * > findMusicFilePath( const QString &find_file_path ) const;
	virtual std::vector< MusicItem * > findMusicMusicSinger( const QString &music_singer ) const;
	virtual MusicItem * findFirstMusicItem( const MusicItem *target ) const;
	virtual MusicItem * findFirstMusicItem( const QString &any_string ) const;
	virtual MusicItem * findFirstMusicName( const QString &music_name ) const;
	virtual MusicItem * findFirstMusicSinger( const QString &music_singer ) const;
	virtual MusicItem * findFirstMusicFilePath( const QString &find_file_path ) const;
	virtual void clearAllMusicItem( );
	virtual void deleteAllMusicItem( );
	virtual void fromMusicIndex( std::vector< MusicItem * > &result_music_item, const std::vector< size_t > &find_index );
	virtual void toMusicIndex( std::vector< size_t > &result_index, const std::vector< MusicItem * > &find_index_music_item );
Q_SIGNALS:
	void signal_change_vector_finished( FavoriteItem *favorite_item );
	void signal_free( FavoriteItem *favorite_item );
};
#endif // FAVORITEITEM_H_H_HEAD__FILE__
