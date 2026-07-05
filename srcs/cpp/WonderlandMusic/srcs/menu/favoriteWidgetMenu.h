#ifndef FAVORITEWIDGETMENU_H_H_HEAD__FILE__
#define FAVORITEWIDGETMENU_H_H_HEAD__FILE__
#include <QMenu>

#include "../interface/iAppCore.h"

class FavoriteWidgetMenu : public QMenu, public IAppCore{
	Q_OBJECT;
public:
	FavoriteWidgetMenu( );

	~FavoriteWidgetMenu( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;

	bool init( ) override;

	bool initAfter( ) override;
};

#endif // FAVORITEWIDGETMENU_H_H_HEAD__FILE__
