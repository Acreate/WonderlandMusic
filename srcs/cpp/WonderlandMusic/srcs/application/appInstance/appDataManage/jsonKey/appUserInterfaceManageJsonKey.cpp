#include "appUserInterfaceManageJsonKey.h"

bool AppUserInterfaceManageJsonKey::init( ) {
	filePath = "/json/app.ui.json";
	mainMenuJsonObject = "main.menu.json.object";
	mainWindowJsonObject = "main.window.json.object";
	return true;
}
const QString & AppUserInterfaceManageJsonKey::getMainWindowJsonObject( ) const {
	return mainWindowJsonObject;
}
const QString & AppUserInterfaceManageJsonKey::getMainMenuJsonObject( ) const {
	return mainMenuJsonObject;
}
