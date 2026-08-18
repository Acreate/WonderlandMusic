#ifndef IMUSICTITLEWIDGET_H_H_HEAD__FILE__
#define IMUSICTITLEWIDGET_H_H_HEAD__FILE__
#include "iMusicWidget.h"

class IMusicItemWidthInfo;
class QMouseEvent;
class QPoint;

class IMusicTitleWidget : public IMusicWidget {
public:
	QString getTypeName( ) const override;
	virtual bool setIMusicItemWidthInfo( IMusicItemWidthInfo *music_item_width_info ) = 0;
	virtual IMusicItemWidthInfo * getIMusicItemWidthInfo( ) const = 0;
};

#endif // IMUSICTITLEWIDGET_H_H_HEAD__FILE__
