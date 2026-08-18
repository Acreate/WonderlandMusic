#ifndef APPRENDERIMAGE_H_H_HEAD__FILE__
#define APPRENDERIMAGE_H_H_HEAD__FILE__

#include <interface/iAppCore.h>

#include "../../../../interface/iAppResourceCore.h"

class IMusicItemWidthInfo;
class IMusicItem;
class IMusicFavoriteItem;
class FavoriteItem;
class ItemWidthInfo;
class MusicItem;
class QSize;
class QWidget;
class QPen;
class QColor;
class QString;
class QImage;
class QFontMetrics;
class QFont;

class AppRenderImage : public IAppCore, public IAppResourceCore {
protected:
	QFont *font = nullptr;
	QFontMetrics *fontMetrics = nullptr;
	QColor *brackGroundColor = nullptr;
	QColor *drawPenColor = nullptr;
	QPen *drawPen = nullptr;

protected:
	bool deleteResource( ) override;
	virtual bool renderTxt( QImage &result_render_image, const QString &render_txt, const QFont &font, const QFontMetrics &font_metrics ) const;
	virtual bool getTxtSize( QSize &result_txt_size, const QString &render_txt, const QFontMetrics &font_metrics ) const;

public:
	AppRenderImage( );

	~AppRenderImage( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	bool init( ) override;

	virtual const QFont * getFont( ) const;

	virtual const QFontMetrics * getFontMetrics( ) const;

	virtual bool renderTxt( QImage &result_render_image, const QString &render_txt ) const;
	virtual bool renderTxt( QImage &result_render_image, const QString &render_txt, const QFont &font ) const;

	virtual bool getTxtSize( QSize &result_txt_size, const QString &render_txt, const QFont &font ) const;
	virtual bool getTxtSize( QSize &result_txt_size, const QString &render_txt ) const;
	virtual bool renderWidget( QImage &result_render_image, QWidget *render_widget ) const;
	virtual bool renderMusicItem( QImage &result_render_image, IMusicItem *music_item, const IMusicItemWidthInfo *item_width_info ) const;
	virtual bool renderMusicItem( QImage &result_render_image, IMusicFavoriteItem *music_favorite_item, const IMusicItemWidthInfo *item_width_info ) const;
};
#endif // APPRENDERIMAGE_H_H_HEAD__FILE__
