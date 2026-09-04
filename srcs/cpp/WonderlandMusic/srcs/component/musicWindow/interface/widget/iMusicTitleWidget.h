#ifndef IMUSICTITLEWIDGET_H_H_HEAD__FILE__
#define IMUSICTITLEWIDGET_H_H_HEAD__FILE__
#include "iMusicWidget.h"

class IMusicItemWidthInfo;
class QMouseEvent;
class QPoint;

class IMusicTitleWidget : public IMusicWidget {
protected:
	~IMusicTitleWidget( ) override;

public:
	virtual bool setPosItemWidthPtrVar( const int *&result_width_var_ptr, int &result_index, int new_width );
	QString getTypeName( ) const override;
	IMusicTitleWidget( );
	virtual bool setMusicItemWidthInfo( IMusicItemWidthInfo *music_item_width_info ) = 0;
	virtual IMusicItemWidthInfo * getIMusicItemWidthInfo( ) const = 0;
	virtual int setAdapiveHeight( const int &adaptive_height ) = 0;
	virtual bool updateMusicItemWidthInfoLayout( ) =0;
};

#endif // IMUSICTITLEWIDGET_H_H_HEAD__FILE__
