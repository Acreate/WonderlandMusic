#ifndef APPMENUMANAGE_H_H_HEAD__FILE__
#define APPMENUMANAGE_H_H_HEAD__FILE__
#include <QObject>

#include "../interface/iAppCore.h"

class QPoint;
class FavoriteWidgetMenu;
class PlayerListWidgetMenu;
class SystemTrayIconMenu;

class AppMenuManage : public QObject, public IAppCore {
	Q_OBJECT;

protected:
	SystemTrayIconMenu *systemTrayIconMenu = nullptr;
	PlayerListWidgetMenu *playerListWidgetMenu = nullptr;
	FavoriteWidgetMenu *favoriteWidgetMenu = nullptr;

public:
	AppMenuManage( );

	~AppMenuManage( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;

	bool init( ) override;

	bool initAfter( ) override;

	virtual bool popSystemTratIconMenu( const QPoint &pos ) const;

	virtual bool popPlayerListWidgetMenu( const QPoint &pos ) const;

	virtual bool popFavoriteWidgetMenu( const QPoint &pos ) const;

	virtual SystemTrayIconMenu * getSystemTrayIconMenu( ) const;

	virtual PlayerListWidgetMenu * getPlayerListWidgetMenu( ) const;

	virtual FavoriteWidgetMenu * getFavoriteWidgetMenu( ) const;
};

#endif // APPMENUMANAGE_H_H_HEAD__FILE__
