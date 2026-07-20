#ifndef FAVORITEWINDOW_H_H_HEAD__FILE__
#define FAVORITEWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>
#include <QObject>
#include "../../interface/iAppCore.h"
#include "../../interface/iAppJsonData.h"
class FavoriteItem;
class FavoriteListWidget;
class FavoriteContentsWidget;

class FavoriteWindow : public QMainWindow, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	FavoriteContentsWidget *favoriteContentsWidget = nullptr;
	FavoriteListWidget *favoriteListWidget = nullptr;

public:
	FavoriteWindow( QWidget *parent );
	~FavoriteWindow( ) override;
	virtual void updateItemInfo( FavoriteItem *favorite_item );
	virtual void deleteItemInfo( FavoriteItem *favorite_item );

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
Q_SIGNALS:
	void signal_loading_json( );
	void signal_loaded_json( );
};
#endif // FAVORITEWINDOW_H_H_HEAD__FILE__
