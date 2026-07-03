#ifndef MUSICCONTROLDOCWIDGET_H_H_HEAD__FILE__
#define MUSICCONTROLDOCWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include "../interface/iAppCore.h"

class PlayerToolsWidget;
class PlayerWindow;

class MusicControlDocWidget : public QDockWidget, public IAppCore {
	Q_OBJECT;

protected:
	PlayerWindow *playerWindow;

	QWidget *titleBarWidget = nullptr;
	PlayerToolsWidget *playerToolsWidget = nullptr;

public:
	MusicControlDocWidget( PlayerWindow *player_window );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;
};

#endif // MUSICCONTROLDOCWIDGET_H_H_HEAD__FILE__
