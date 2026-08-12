#include "appUserInterfaceManageJsonKey.h"

bool AppUserInterfaceManageJsonKey::init( ) {
	filePath = "/json/app.ui.json";
	mainWindow = "main.window.info";
	musicListTopWidget = "music.window.list.top.info";
	musicFavoriteWidget = "music.window.favorite.info";
	return true;
}

const QString & AppUserInterfaceManageJsonKey::getMainWindow( ) const {
	return mainWindow;
}

const QString & AppUserInterfaceManageJsonKey::getMusicListTopWidget( ) const {
	return musicListTopWidget;
}

const QString & AppUserInterfaceManageJsonKey::getMusicFavoriteWidget( ) const {
	return musicFavoriteWidget;
}
