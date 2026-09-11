#ifndef PLAYERWINDOWCENTRECHILDWIDGET_H_H_HEAD__FILE__
#define PLAYERWINDOWCENTRECHILDWIDGET_H_H_HEAD__FILE__
#include "../../../../classTypeInfo/classTypeInfoVar.h"

class QWidget;
class IPlayerWindowCentreWidget;

class IPlayerWindowCentreChildWidget : public virtual ClassTypeInfoVar {
protected:
	IPlayerWindowCentreChildWidget( );
	~IPlayerWindowCentreChildWidget( ) override;

public:
	virtual QWidget * toWidget( ) = 0;
	virtual bool setPlayerWindowCentre( IPlayerWindowCentreWidget *play_window ) =0;
	virtual IPlayerWindowCentreWidget * getPlayerWindowCentre( ) const = 0;
	virtual bool updateLayout( ) = 0;
};

#endif // PLAYERWINDOWCENTRECHILDWIDGET_H_H_HEAD__FILE__
