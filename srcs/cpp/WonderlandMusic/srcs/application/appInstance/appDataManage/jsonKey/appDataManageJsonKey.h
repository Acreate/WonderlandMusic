#ifndef APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
#include <interface/iJsonKey.h>

class AppDataManageJsonKey : public IJsonKey {
	QString uiJsonObject;
	QString appSettingPath;
	QString musicItemWidthInfo;
	QString musicWidgetSizetInfo;

public:
	bool init( ) override;
	virtual const QString & getUiJsonObject( ) const;
	virtual const QString & getAppSettingPath( ) const;
	virtual const QString & getMusicItemWidthInfo( ) const;
	virtual const QString & getMusicWidgetSizetInfo( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( AppDataManage );
}
#endif // APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
