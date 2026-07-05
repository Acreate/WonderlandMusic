#ifndef FAVORITEMDOCKWIDGET_H_H_HEAD__FILE__
#define FAVORITEMDOCKWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class FavoriteSrollArea;
class FavoriteWidget;
class PlayerWindow;

class FavoritemDockWidget : public QDockWidget, public IAppCore {
	Q_OBJECT;

protected:
	PlayerWindow *playerWindow;
	QWidget *titleBarWidget = nullptr;
	FavoriteSrollArea *favoriteSrollArea = nullptr;

public:
	FavoritemDockWidget( PlayerWindow *player_window );

	~FavoritemDockWidget( ) override;

	virtual FavoriteSrollArea * getFavoriteSrollArea( ) const;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;
};

#endif // FAVORITEMDOCKWIDGET_H_H_HEAD__FILE__
