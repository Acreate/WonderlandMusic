#ifndef FAVORITEWIDGET_H_H_HEAD__FILE__
#define FAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class PlayerListWidget;
class FavoriteItemWidget;
class PlayerWindow;

class FavoriteWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;

public:
	FavoriteWidget( QWidget *parent );

protected:
	bool deleteResource( ) override;

public:
	~FavoriteWidget( ) override;

	bool init( ) override;

	virtual void updateLayout( );

	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

Q_SIGNALS:
	void clickFavoriteItem( const FavoriteItemWidget *item );
};

#endif // FAVORITEWIDGET_H_H_HEAD__FILE__
