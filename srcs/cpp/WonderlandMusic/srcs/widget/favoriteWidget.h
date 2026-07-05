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

	virtual bool appendFavoriteItem( const QString &create_favorite_name );

	virtual bool removeFavoriteItem( const QString &remove_favorite_name );

	virtual bool resetFavoriteItem( const std::vector< QString > &create_favorite_vector );
};

#endif // FAVORITEWIDGET_H_H_HEAD__FILE__
