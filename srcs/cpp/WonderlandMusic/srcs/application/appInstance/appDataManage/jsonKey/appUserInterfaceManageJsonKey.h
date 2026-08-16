#ifndef APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
#include <interface/iJsonKey.h>

class AppUserInterfaceManageJsonKey : public IJsonKey {
	QString mainWindowJsonObject;
	QString mainMenuJsonObject;

public:
	bool init( ) override;
	virtual const QString & getMainWindowJsonObject( ) const;
	virtual const QString & getMainMenuJsonObject( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( AppUserInterfaceManage );
}

#endif // APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
