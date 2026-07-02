#ifndef MUSICITEMSIZEINFODOCKWIDGET_H_H_HEAD__FILE__
#define MUSICITEMSIZEINFODOCKWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include "../application/appCore.h"

class PlayerListTopWidget;
class QScrollArea;
class PlayerWindow;

class MusicItemSizeInfoDockWidget : public QDockWidget, public AppCore {
	Q_OBJECT;

protected:
	PlayerWindow *playerWindow;

	QScrollArea *playerListTopWidgetScrollArea = nullptr;
	PlayerListTopWidget *playerListTopWidget = nullptr;
	QWidget *titleBarWidget = nullptr;

public:
	MusicItemSizeInfoDockWidget( PlayerWindow *player_window );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	virtual QScrollArea * getPlayerListTopWidgetScrollArea( ) const {
		return playerListTopWidgetScrollArea;
	}

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const {
		return playerListTopWidget;
	}

	virtual QWidget * getTitleBarWidget( ) const {
		return titleBarWidget;
	}

Q_SIGNALS:
	void horizontalScroll( int new_point );

	void verticalScroll( int new_point );
};

#endif // MUSICITEMSIZEINFODOCKWIDGET_H_H_HEAD__FILE__
