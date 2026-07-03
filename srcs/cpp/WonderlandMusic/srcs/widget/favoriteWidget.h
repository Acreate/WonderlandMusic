#ifndef FAVORITEWIDGET_H_H_HEAD__FILE__
#define FAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../application/appCore.h"

class PlayerListWidget;
class FavoriteItemWidget;
class PlayerWindow;

class FavoriteWidget : public QWidget, public AppCore {
	Q_OBJECT;

protected:
	FavoriteItemWidget *rootFavoriteItemWidget = nullptr;
	std::vector< FavoriteItemWidget * > favoriteItemWidgetVector;

public:
	FavoriteWidget( QWidget *parent );

protected:
	bool deleteResource( ) override;

public:
	~FavoriteWidget( ) override;

	bool init( ) override;

	virtual bool craeteItem( const QString &item_name, FavoriteItemWidget *&result_create_item );

	virtual bool craeteItem( const QString &item_name, PlayerListWidget *item_widget, FavoriteItemWidget *&result_create_item );

	virtual void updateLayout( );

	virtual void clearItem( );

	virtual FavoriteItemWidget * getRootFavoriteItemWidget( ) const;

	virtual const std::vector< FavoriteItemWidget * > & getFavoriteItemWidgetVector( ) const;

Q_SIGNALS:
	void clickFavoriteItem( const FavoriteItemWidget *item );
};

#endif // FAVORITEWIDGET_H_H_HEAD__FILE__
