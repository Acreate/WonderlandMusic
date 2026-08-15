#ifndef APPMENUMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPMENUMANAGEJSONKEY_H_H_HEAD__FILE__
#include <interface/iJsonKey.h>

class AppMenuManageJsonKey : public IJsonKey {
public:
	bool init( ) override;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( AppMenuManage );
}
#endif // APPMENUMANAGEJSONKEY_H_H_HEAD__FILE__
