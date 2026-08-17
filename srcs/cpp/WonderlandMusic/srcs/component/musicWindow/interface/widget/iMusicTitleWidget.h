#ifndef IMUSICTITLEWIDGET_H_H_HEAD__FILE__
#define IMUSICTITLEWIDGET_H_H_HEAD__FILE__
#include "iMusicWidget.h"

#include <interface/iAppCore.h>

class QMouseEvent;
class QPoint;

class IMusicTitleWidget : public IAppCore, public IMusicWidget {
public:
	QString getTypeName( ) const override;
	virtual bool sendMouseMoveEvent( const QMouseEvent &mouse_event ) = 0;
	virtual bool sendMouseRelaseEvent( const QMouseEvent &mouse_event ) =0;
	virtual bool sendMousePressEvent( const QMouseEvent &mouse_event ) = 0;
};

#endif // IMUSICTITLEWIDGET_H_H_HEAD__FILE__
