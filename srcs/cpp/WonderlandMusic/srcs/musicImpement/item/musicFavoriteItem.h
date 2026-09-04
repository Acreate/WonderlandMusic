#ifndef MUSICFAVORITEITEM_H_H_HEAD__FILE__
#define MUSICFAVORITEITEM_H_H_HEAD__FILE__
#include <component/musicWindow/interface/item/iMusicFavoriteItem.h>

class MusicInfoItem;
class MusicInfo;
class MusicFavoriteItemWidget;

class MusicFavoriteItem : public QObject, public IMusicFavoriteItem {
	Q_OBJECT;

protected:
	UserMutex *musicFavoriteItemUserMutex;
	QString name;
	std::vector< MusicInfoItem * > musicItemVector;
	IMusicCentreWidget *musicCentreWidget = nullptr;
	MusicFavoriteItemWidget *musicFavoriteItemWidget = nullptr;

public:
	MusicFavoriteItem( );
	~MusicFavoriteItem( ) override;

public:
	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;
	virtual MusicInfoItem * load( MusicInfo *music_info );
	virtual std::vector< MusicInfoItem * > load( const std::vector< MusicInfo * > &music_infos );
	bool getName( QString &result_name ) const override;
	bool removeMusicItem( IMusicItem *music_item ) override;
	bool clear( ) override;
	bool update( ) override;
	bool fromYPosGetMusicItem( IMusicItem *&result_music_item, const size_t &y_pos ) const override;
	bool fromIndexGetMusicItem( IMusicItem *&result_music_item, const size_t &index ) const override;
	bool fromMusicItemGetIndex( size_t &result_index, const IMusicItem *music_item ) const override;
	bool fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &music_name ) const override;
	bool fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) const override;
	bool fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &absolute_file_path ) const override;
	bool fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) const override;
	size_t getMusicVector( std::vector< IMusicItem * > &result_clone_vector ) const override;
	virtual void setName( const QString &name );
	IMusicCentreWidget * getMusicCentreWidget( ) const override;
	IMusicFavoriteItemWidget * getMusicFavoriteItemWidget( ) const override;
	bool loadMusicDirPath( const std::vector< QString > &music_file_path ) override;
	bool loadMusicFile( const std::vector< QString > &music_file_path ) override;
	bool loadMusicFile( const QString &music_file_path ) override;
};

#endif // MUSICFAVORITEITEM_H_H_HEAD__FILE__
