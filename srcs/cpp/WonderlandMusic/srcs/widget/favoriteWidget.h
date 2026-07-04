#ifndef FAVORITEWIDGET_H_H_HEAD__FILE__
#define FAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class PlayerListWidget;
class FavoriteItemWidget;
class PlayerWindow;

class FavoriteWidget : public QWidget, public IAppCore {
	Q_OBJECT;

public:
	FavoriteWidget( QWidget *parent );

protected:
	bool deleteResource( ) override;

public:
	~FavoriteWidget( ) override;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	virtual void updateLayout( );

Q_SIGNALS:
	void clickFavoriteItem( const FavoriteItemWidget *item );
};

#endif // FAVORITEWIDGET_H_H_HEAD__FILE__
