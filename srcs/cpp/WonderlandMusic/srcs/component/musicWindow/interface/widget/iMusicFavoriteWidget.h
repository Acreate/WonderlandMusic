#ifndef IMUSICFAVORITEWIDGET_H_H_HEAD__FILE__
#define IMUSICFAVORITEWIDGET_H_H_HEAD__FILE__

#include "iMusicWidget.h"

class QString;
class QPoint;
class QPainter;
class IMusicFavoriteItem;
class QWidget;

class IMusicFavoriteWidget : public IMusicWidget {
public:
	QString getTypeName( ) const override;
	virtual bool fromYPosGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &pos_y ) const = 0;
	virtual bool fromIndexGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &index ) const = 0;
	virtual bool fromNameGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const QString &index ) const = 0;
};

#endif // IMUSICFAVORITEWIDGET_H_H_HEAD__FILE__
