#include "pathInfoTools.h"

#include "instanceTools.h"

#include "../application/appDataManage.h"
bool PathInfoTools::getAppSettintHomePath( QString &result_app_setting_home_path ) {
	auto appDataManage = InstanceTools::getAppDataManage( );
	if( appDataManage == nullptr )
		return false;
	result_app_setting_home_path = appDataManage->getAppSettingPath( );
	return true;
}
