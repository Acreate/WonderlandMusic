#ifndef MUSICTOOLDOCKWIDGET_H_H_HEAD__FILE__
#define MUSICTOOLDOCKWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include <interface/iAppCore.h>

class DockWidgetTitleWidget;
class MusicToolWidget;

class MusicToolDockWidget : public QDockWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicWindow;

private:
	MusicToolWidget *musicToolWidget = nullptr;
	DockWidgetTitleWidget *dockWidgetTitleWidget = nullptr;
	MusicWindow *musicWindow = nullptr;
	MusicToolDockWidget( MusicWindow *music_window );
	~MusicToolDockWidget( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};

#endif // MUSICTOOLDOCKWIDGET_H_H_HEAD__FILE__
