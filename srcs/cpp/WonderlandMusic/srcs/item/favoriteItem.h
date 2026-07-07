#ifndef FAVORITEITEM_H_H_HEAD__FILE__
#define FAVORITEITEM_H_H_HEAD__FILE__
#include "../interface/iAppJsonData.h"
class FavoriteItemWidget;
class MusicItem;

class FavoriteItem : public QObject, public IAppJsonData {
	Q_OBJECT;

protected:
	class ItemInfo {
		friend class FavoriteItem;
		QString name;
		std::vector< MusicItem * > musicItemvVector;
		FavoriteItemWidget *favoriteItemWidget;
		QObject *deleteErrorObj;
		ItemInfo( const QString &name, const std::vector< MusicItem * > &music_itemv_vector, FavoriteItemWidget *favorite_item_widget );

	public:
		virtual ~ItemInfo( );
	};

	ItemInfo *info;

public:
	FavoriteItem( const QString &name, const std::vector< MusicItem * > &music_itemv_vector );
	virtual void setEnabled( bool enabled );
	FavoriteItem( const QString &name );
	~FavoriteItem( ) override;
	virtual void setFavoriteName( const QString &favorite_name );
	virtual QString getFavoriteName( ) const;
	virtual FavoriteItemWidget * getFavoriteItemWidget( ) const;

public:
	static bool getJsonDataVector( QJsonObject &get_json_object, const std::vector< FavoriteItem * > &conver_vector );
	static bool setJsonDataVector( std::vector< FavoriteItem * > &result_vector, const QJsonObject &set_json_object );

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual const QString & getName( ) const;
	virtual const std::vector< MusicItem * > & getMusicItemvVector( ) const;
	virtual bool appendMusicItem( MusicItem *music_item );
	virtual std::vector< MusicItem * > findMusicName( const QString &find_name ) const;
	virtual std::vector< MusicItem * > findMusicFilePath( const QString &find_file_path ) const;
	virtual std::vector< MusicItem * > findMusicMusicSinger( const QString &music_singer ) const;
Q_SIGNALS:
	void signal_change_name_finished( );
	void signal_change_vector_finished( );
};
#endif // FAVORITEITEM_H_H_HEAD__FILE__
