#ifndef MUSICITEMSIZEINFODOCKWIDGET_H_H_HEAD__FILE__
#define MUSICITEMSIZEINFODOCKWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include "../interface/iAppCore.h"

class PlayerListTopWidget;
class QScrollArea;
class PlayerWindow;

class MusicItemSizeInfoDockWidget : public QDockWidget, public IAppCore {
	Q_OBJECT;

protected:
	QMainWindow *mainWindow;

	QScrollArea *playerListTopWidgetScrollArea = nullptr;
	PlayerListTopWidget *playerListTopWidget = nullptr;
	QWidget *titleBarWidget = nullptr;

public:
	MusicItemSizeInfoDockWidget( QMainWindow *main_window );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	virtual QScrollArea * getPlayerListTopWidgetScrollArea( ) const;

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const;

	virtual QWidget * getTitleBarWidget( ) const;

Q_SIGNALS:
	void signal_changed_width( int split_width, int widget_before_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width );
};

#endif // MUSICITEMSIZEINFODOCKWIDGET_H_H_HEAD__FILE__
