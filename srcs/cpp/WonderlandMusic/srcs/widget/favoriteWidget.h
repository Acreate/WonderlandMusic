#ifndef FAVORITEWIDGET_H_H_HEAD__FILE__
#define FAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppDiskJsonData.h"

class PlayerListWidget;
class FavoriteItemWidget;
class PlayerWindow;

class FavoriteWidget : public QWidget, public IAppCore, public IAppDiskJsonData {
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

	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	bool readJsonData( ) override;

	bool writeJsonData( ) override;

Q_SIGNALS:
	void clickFavoriteItem( const FavoriteItemWidget *item );
};

#endif // FAVORITEWIDGET_H_H_HEAD__FILE__
