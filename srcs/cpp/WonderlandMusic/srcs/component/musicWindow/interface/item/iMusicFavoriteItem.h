#ifndef IMUSICFAVORITEITEM_H_H_HEAD__FILE__
#define IMUSICFAVORITEITEM_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicItem;
class QString;
class QImage;

class IMusicFavoriteItem : public IMusicCentreWidgetChild {
	friend class AppRenderImage;

protected:
	virtual bool setNameDrawBuff( QImage &image ) = 0;
	virtual bool setMusicItemVectorDrawBuff( QImage &image ) = 0;

public:
	IMusicFavoriteItem( );
	virtual bool getName( QString &result_name ) const = 0;
	virtual bool addMusicItem( IMusicItem *music_item ) = 0;
	virtual bool removeMusicItem( IMusicItem *music_item ) = 0;
	virtual bool clear( ) = 0;
	virtual bool getNameDrawBuff( QImage &result_buff ) const = 0;
	virtual bool getMusicItemVectorDrawBuff( QImage &result_buff ) const = 0;
	virtual bool update( ) = 0;
	virtual bool fromIndexGetMusicItem( IMusicItem * &result_music_item_vector, const size_t &result_count ) = 0;
	virtual bool fromMusicItemGetIndex( size_t &result_index, const IMusicItem *music_item ) = 0;
	virtual bool fromNameGetFirstMusicItem( IMusicItem * &result_music_item, const QString &name ) = 0;
	virtual bool fromFileBaseNameGetFirstMusicItem( IMusicItem * &result_music_item, const QString &file_base_name ) = 0;
	virtual bool fromFileAbsPathGetFirstMusicItem( IMusicItem * &result_music_item, const QString &path ) = 0;
	virtual bool fromSingerGetFirstMusicItem( IMusicItem * &result_music_item, const QString &singer ) = 0;
	virtual size_t getMusicVectorClone( std::vector< IMusicItem * > &result_clone_vector ) const = 0;
};

#endif // IMUSICFAVORITEITEM_H_H_HEAD__FILE__
