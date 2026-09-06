#ifndef PLAYWINDOW_H_H_HEAD__FILE__
#define PLAYWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../../interface/iAppCore.h"
#include "../../interface/iAppResourceCore.h"

class PlayerInfoListWidgetScrollArea;
class PlayerControlWidgetScrollArea;
class IPlayerControlWidget;
class IPlayerInfoListWidget;

class PlayWindow : public QMainWindow, public IAppResourceCore, public IAppCore {
	Q_OBJECT;

private:
	UserMutex *userMutex = nullptr;
	IPlayerInfoListWidget *playerInfoListWidget = nullptr;
	IPlayerControlWidget *playerControlWidget = nullptr;
	PlayerControlWidgetScrollArea *playerControlWidgetScrollArea = nullptr;
	PlayerInfoListWidgetScrollArea *playerInfoListWidgetScrollArea = nullptr;

public:
	PlayWindow( QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags( ) );
	~PlayWindow( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual IPlayerInfoListWidget * getPlayerInfoListWidget( ) const;
	virtual IPlayerInfoListWidget * setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget );
	virtual IPlayerControlWidget * getPlayerControlWidget( ) const;
	virtual IPlayerControlWidget * setPlayerControlWidget( IPlayerControlWidget *player_control_widget );
	virtual bool updateLayout( );
};

#endif // PLAYWINDOW_H_H_HEAD__FILE__
