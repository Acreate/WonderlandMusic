#ifndef APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
#include <interface/iJsonKey.h>

class AppDataManageJsonKey : public IJsonKey {
	QString appMusicManageJsonObject;
	QString uiJsonObject;
	QString appSettingPath;

public:
	bool init( ) override;
	virtual const QString & getAppMusicManageJsonObject( ) const;
	virtual const QString & getUiJsonObject( ) const;
	virtual const QString & getAppSettingPath( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( AppDataManage );
}
#endif // APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
