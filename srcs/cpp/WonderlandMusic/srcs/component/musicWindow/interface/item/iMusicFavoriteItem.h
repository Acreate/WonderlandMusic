#ifndef IMUSICFAVORITEITEM_H_H_HEAD__FILE__
#define IMUSICFAVORITEITEM_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicFavoriteItemWidget;
class IMusicItem;
class QString;
class QImage;

class IMusicFavoriteItem : public IMusicCentreWidgetChild {
protected:
	~IMusicFavoriteItem( ) override;

public:
	IMusicFavoriteItem( );
	virtual bool getName( QString &result_name ) const = 0;
	virtual bool removeMusicItem( IMusicItem *music_item ) = 0;
	virtual bool clear( ) = 0;
	virtual bool update( ) = 0;
	virtual size_t getMusicVector( std::vector< IMusicItem * > &result_clone_vector ) const = 0;
	virtual IMusicFavoriteItemWidget * getMusicFavoriteItemWidget( ) const = 0;
	virtual bool loadMusicDirPath( const std::vector< QString > &music_file_path ) = 0;
	virtual bool loadMusicFile( const std::vector< QString > &music_file_path ) = 0;
	virtual bool loadMusicFile( const QString &music_file_path ) = 0;
};

#endif // IMUSICFAVORITEITEM_H_H_HEAD__FILE__
