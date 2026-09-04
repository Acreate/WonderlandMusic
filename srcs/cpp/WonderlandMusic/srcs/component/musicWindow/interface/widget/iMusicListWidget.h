#ifndef IMUSICLISTWIDGET_H_H_HEAD__FILE__
#define IMUSICLISTWIDGET_H_H_HEAD__FILE__
#include "iMusicWidget.h"

class IMusicFavoriteItem;
class QString;
class IMusicItem;

class IMusicListWidget : public IMusicWidget {
protected:
	~IMusicListWidget( ) override;

public:
	QString getTypeName( ) const override;
	IMusicListWidget( );
	virtual IMusicFavoriteItem * getCurrentMusicFavoriteItem( ) const =0;
	virtual bool setCurrentMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) =0;
	virtual bool fromYPosGetMusicItem( IMusicItem * &result_music_item, const size_t &y_pos ) const = 0;
	virtual bool fromIndexGetMusicItem( IMusicItem * &result_music_item, const size_t &index ) const = 0;
	virtual bool fromNameGetFirstMusicItem( IMusicItem * &result_music_item, const QString &name ) const = 0;
	virtual bool fromFileBaseNameGetFirstMusicItem( IMusicItem * &result_music_item, const QString &file_base_name ) const = 0;
	virtual bool fromFileAbsPathGetFirstMusicItem( IMusicItem * &result_music_item, const QString &path ) const = 0;
	virtual bool fromSingerGetFirstMusicItem( IMusicItem * &result_music_item, const QString &singer ) const = 0;
};

#endif // IMUSICLISTWIDGET_H_H_HEAD__FILE__
