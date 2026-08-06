#ifndef APPDATAJSONKEY_H_H_HEAD__FILE__
#define APPDATAJSONKEY_H_H_HEAD__FILE__
#include "../interface/iAppCore.h"
#include <head/head_json_key_class.h>

class MusicWindowJsonKey;

class AppDataJsonKey : public IAppCore {
protected:
	AboutWidgetJsonKey *aboutWidget = nullptr;
	MainWindowJsonKey *mainWindow = nullptr;
	SystemTrayIconJsonKey *systemTrayIcon = nullptr;
	AppDataManageJsonKey *appDataManage = nullptr;
	AppUserInterfaceManageJsonKey *appUserInterfaceManage = nullptr;
	AppMusicManageJsonKey *appMusicManage = nullptr;
	MusicWindowJsonKey* musicWindow = nullptr;
protected:
	bool deleteResource( ) override;

public:
	~AppDataJsonKey( ) override;
	AppDataJsonKey( );
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
	virtual MusicWindowJsonKey * getMusicWindow( ) const;
	virtual AboutWidgetJsonKey * getAboutWidget( ) const;
	virtual MainWindowJsonKey * getMainWindow( ) const;
	virtual SystemTrayIconJsonKey * getSystemTrayIcon( ) const;
	virtual AppDataManageJsonKey * getAppDataManage( ) const;
	virtual AppUserInterfaceManageJsonKey * getAppUserInterfaceManage( ) const;
	virtual AppMusicManageJsonKey * getAppMusicManage( ) const;
};
#endif // APPDATAJSONKEY_H_H_HEAD__FILE__
