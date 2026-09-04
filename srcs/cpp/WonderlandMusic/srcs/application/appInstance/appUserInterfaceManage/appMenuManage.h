#ifndef APPMENUMANAGE_H_H_HEAD__FILE__
#define APPMENUMANAGE_H_H_HEAD__FILE__
#include <interface/iAppCore.h>
#include <interface/iAppJsonData.h>

#include "../../../interface/iAppResourceCore.h"

class MusicListMenu;
class MusicFavoriteMenu;
class IMusicListMenu;
class IMusicFavoriteMenu;
class SystemTrayIconMenu;
class QPoint;

class AppMenuManage : public QObject, public IAppCore, public IAppJsonData, public IAppResourceCore {
	Q_OBJECT;

protected:
	SystemTrayIconMenu *systemTrayIconMenu = nullptr;
	MusicFavoriteMenu *musicFavoriteMenu = nullptr;
	MusicListMenu *musicListMenu = nullptr;

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
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};

#endif // APPMENUMANAGE_H_H_HEAD__FILE__
