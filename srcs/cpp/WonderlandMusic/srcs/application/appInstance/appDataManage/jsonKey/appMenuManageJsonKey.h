#ifndef APPMENUMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPMENUMANAGEJSONKEY_H_H_HEAD__FILE__
#include <interface/iJsonKey.h>

class AppMenuManageJsonKey : public IJsonKey {
	QString musicFavoriteMenuJsonObjectKey;
	QString musicListMenuJsonObjectKey;

public:
	bool init( ) override;
	virtual const QString & getMusicFavoriteMenuJsonObjectKey( ) const;
	virtual const QString & getMusicListMenuJsonObjectKey( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( AppMenuManage );
}
#endif // APPMENUMANAGEJSONKEY_H_H_HEAD__FILE__
