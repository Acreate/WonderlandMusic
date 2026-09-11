#ifndef IPLAYERWINDOWCENTREWIDGET_H_H_HEAD__FILE__
#define IPLAYERWINDOWCENTREWIDGET_H_H_HEAD__FILE__

#include <interface/iAppResourceCore.h>

#include "../../../../classTypeInfo/classTypeInfoVar.h"

class IPlayerControlWidget;
class PlayWindow;
class IPlayerInfoListWidget;

class IPlayerWindowCentreWidget : public IAppResourceCore, public virtual ClassTypeInfoVar {
protected:
	IPlayerWindowCentreWidget( );
	~IPlayerWindowCentreWidget( ) override;

public:
	virtual PlayWindow * getPlayWindow( ) const = 0;
	virtual bool setPlayWindow( PlayWindow *play_window ) = 0;
	virtual bool setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget ) = 0;
	virtual bool setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) = 0;
	virtual QWidget * toWidget( ) = 0;
	virtual bool updateLayout( ) = 0;
	virtual IPlayerInfoListWidget * getPlayerInfoListWidget( ) const = 0;
	virtual IPlayerControlWidget * getPlayerControlWidget( ) const = 0;
};

#endif // IPLAYERWINDOWCENTREWIDGET_H_H_HEAD__FILE__
