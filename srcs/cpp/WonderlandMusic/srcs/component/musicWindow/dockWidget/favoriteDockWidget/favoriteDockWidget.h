#ifndef FAVORITEDOCKWIDGET_H_H_HEAD__FILE__
#define FAVORITEDOCKWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include <interface/iAppCore.h>

class DockWidgetTitleWidget;
class FavoriteListWidget;

class FavoriteDockWidget : public QDockWidget, public IAppCore {
	Q_OBJECT;
	friend class MusicWindow;

private:
	MusicWindow *musicWindow = nullptr;
	FavoriteListWidget *favoriteListWidget = nullptr;
	DockWidgetTitleWidget *dockWidgetTitleWidget = nullptr;

	FavoriteDockWidget( MusicWindow *music_window );

protected:
	bool deleteResource( ) override;
	~FavoriteDockWidget( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;

	virtual void updateDockSize( );
};

#endif // FAVORITEDOCKWIDGET_H_H_HEAD__FILE__
