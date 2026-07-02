#ifndef MUSICCONTREWIDGET_H_H_HEAD__FILE__
#define MUSICCONTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../application/appCore.h"

class PlayerListWidgetMenu;
class PlayerWindow;

class MusicContreWidget : public QWidget, public AppCore {
	Q_OBJECT;

protected:
	PlayerWindow *playerWindow;
	/// @brief 列表菜单
	PlayerListWidgetMenu *playerListWidgetMenu = nullptr;

public:
	MusicContreWidget( PlayerWindow *player_window );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;
};

#endif // MUSICCONTREWIDGET_H_H_HEAD__FILE__
