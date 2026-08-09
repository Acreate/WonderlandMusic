#ifndef APPMENUMANAGE_H_H_HEAD__FILE__
#define APPMENUMANAGE_H_H_HEAD__FILE__
#include <QObject>

#include "../interface/iAppCore.h"

class IMusicListMenu;
class IMusicFavoriteMenu;
class SystemTrayIconMenu;
class QPoint;

class AppMenuManage : public QObject, public IAppCore {
	Q_OBJECT;

protected:
	SystemTrayIconMenu *systemTrayIconMenu = nullptr;
	IMusicFavoriteMenu *musicFavoriteMenu = nullptr;
	IMusicListMenu *musicListMenu = nullptr;

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
	virtual bool popMusicFavoriteMenu( const QPoint &pos ) const;
	virtual bool popMusicListMenu( const QPoint &pos ) const;

	virtual SystemTrayIconMenu * getSystemTrayIconMenu( ) const;
	virtual IMusicFavoriteMenu * getMusicFavoriteMenu( ) const;
	virtual IMusicListMenu * getMusicListMenu( ) const;
};

#endif // APPMENUMANAGE_H_H_HEAD__FILE__
