#ifndef IMUSICTITLEWIDGET_H_H_HEAD__FILE__
#define IMUSICTITLEWIDGET_H_H_HEAD__FILE__
#include "iMusicWidget.h"

class IMusicItemWidthInfo;
class QMouseEvent;
class QPoint;

class IMusicTitleWidget : public IMusicWidget {
protected:
	virtual bool setPosItemWidthPtrVar( const int *&result_width_var_ptr, int &result_index, int new_width );

public:
	QString getTypeName( ) const override;
	IMusicTitleWidget( );
	~IMusicTitleWidget( ) override;
	virtual bool setIMusicItemWidthInfo( IMusicItemWidthInfo *music_item_width_info ) = 0;
	virtual IMusicItemWidthInfo * getIMusicItemWidthInfo( ) const = 0;
};

#endif // IMUSICTITLEWIDGET_H_H_HEAD__FILE__
