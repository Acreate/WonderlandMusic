#ifndef MUSICFAVORITEITEM_H_H_HEAD__FILE__
#define MUSICFAVORITEITEM_H_H_HEAD__FILE__

#include "../component/musicWindow/interface/item/iMusicFavoriteItem.h"

class MusicFavoriteItem : public QObject, public IMusicFavoriteItem {
	Q_OBJECT;

protected:
	UserMutex *musicFavoriteItemUserMutex;
	QString name;
	std::vector< IMusicItem * > musicItemVector;
	MusicCentreWidget *musicCentreWidget = nullptr;

public:
	MusicFavoriteItem( );
	~MusicFavoriteItem( ) override;

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	bool getName( QString &result_name ) const override;
	bool addMusicItem( IMusicItem *music_item ) override;
	bool removeMusicItem( IMusicItem *music_item ) override;
	bool clear( ) override;
	bool update( ) override;
	bool fromIndexGetMusicItem( IMusicItem *&result_music_item_vector, const size_t &result_count ) override;
	bool fromMusicItemGetIndex( size_t &result_index, const IMusicItem *music_item ) override;
	bool fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) override;
	bool fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) override;
	bool fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) override;
	bool fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) override;
	size_t getMusicVectorClone( std::vector< IMusicItem * > &result_clone_vector ) const override;
	virtual void setName( const QString &name );
};

#endif // MUSICFAVORITEITEM_H_H_HEAD__FILE__
