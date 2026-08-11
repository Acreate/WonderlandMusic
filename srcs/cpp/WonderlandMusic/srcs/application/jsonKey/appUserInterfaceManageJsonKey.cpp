#include "appUserInterfaceManageJsonKey.h"
#include "../../tools/pathInfoTools.h"

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

QString AppUserInterfaceManageJsonKey::getFilePath( ) const {
	QString applicationDirPath;
	if( PathInfoTools::getAppSettintHomePath( applicationDirPath ) )
		return applicationDirPath + filePath;
	return filePath;
}

const QString & AppUserInterfaceManageJsonKey::getMusicListTopWidget( ) const {
	return musicListTopWidget;
}

const QString & AppUserInterfaceManageJsonKey::getMusicFavoriteWidget( ) const {
	return musicFavoriteWidget;
}
