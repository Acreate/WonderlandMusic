#ifndef IMUSICLISTWIDGET_H_H_HEAD__FILE__
#define IMUSICLISTWIDGET_H_H_HEAD__FILE__
#include "iMusicWidget.h"

#include <interface/iAppCore.h>

class IMusicFavoriteItem;
class QString;
class IMusicItem;

class IMusicListWidget : public IAppCore, public IMusicWidget {
public:
	QString getTypeName() const override;
	virtual IMusicFavoriteItem * getCurrentMusicFavoriteItem( ) const =0;
	virtual bool setCurrentMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) =0;
	virtual bool fromYPosGetMusicItem( IMusicItem * &result_music_item, const size_t &y_pos ) = 0;
	virtual bool fromIndexGetMusicItem( IMusicItem * &result_music_item, const size_t &index ) = 0;
	virtual bool fromNameGetFirstMusicItem( IMusicItem * &result_music_item, const QString &name ) = 0;
	virtual bool fromFileBaseNameGetFirstMusicItem( IMusicItem * &result_music_item, const QString &file_base_name ) = 0;
	virtual bool fromFileAbsPathGetFirstMusicItem( IMusicItem * &result_music_item, const QString &path ) = 0;
	virtual bool fromSingerGetFirstMusicItem( IMusicItem * &result_music_item, const QString &singer ) = 0;
};

#endif // IMUSICLISTWIDGET_H_H_HEAD__FILE__
