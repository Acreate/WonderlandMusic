#ifndef PLAYWINDOW_H_H_HEAD__FILE__
#define PLAYWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include <interface/iAppResourceCore.h>

#include "../../classTypeInfo/classTypeInfoVar.h"

class IPlayerWindowCentreWidget;
class UserMutex;
class PlayerInfoListWidgetScrollArea;
class PlayerControlWidgetScrollArea;
class IPlayerControlWidget;
class IPlayerInfoListWidget;

class PlayWindow : public QMainWindow, public IAppResourceCore, public virtual ClassTypeInfoVar {
	Q_OBJECT;

private:
	UserMutex *userMutex = nullptr;
	IPlayerWindowCentreWidget *playerWindowCentreWidget = nullptr;

public:
	PlayWindow( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~PlayWindow( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual IPlayerWindowCentreWidget * getPlayerWindowCentreWidget( ) const;
	virtual bool setPlayerWindowCentreWidget( IPlayerWindowCentreWidget *const player_window_centre_widget );
	virtual IPlayerInfoListWidget * getPlayerInfoListWidget( ) const;
	virtual bool setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget );
	virtual IPlayerControlWidget * getPlayerControlWidget( ) const;
	virtual bool setPlayerControlWidget( IPlayerControlWidget *player_control_widget );
	virtual bool updateLayout( );
};

#endif // PLAYWINDOW_H_H_HEAD__FILE__
