#include "instanceTools.h"

#include "../application/appInstance.h"
#include "../application/appInstance/appDataManage.h"
#include "../application/appInstance/appUserInterfaceManage.h"
#include "../application/appInstance/appDataManage/appMusicManage.h"
#include "../application/appInstance/appUserInterfaceManage/appDrawManage.h"

#define If_Nullptr_Result_Nullptr( ptr_ ) 	if( ptr_ == nullptr ) return nullptr
AppDataManage * InstanceTools::getAppDataManage( ) {
	auto appInstance = InstanceTools::getAppInstance( );
	If_Nullptr_Result_Nullptr( appInstance );
	return appInstance->getAppDataManage( );
}
AppDataJsonKey * InstanceTools::getAppDataJsonKey( ) {
	auto dataManage = InstanceTools::getAppDataManage( );
	If_Nullptr_Result_Nullptr( dataManage );
	return dataManage->getAppDataJsonKey( );
}
AppDateTimerManage * InstanceTools::getAppDateTimerManage( ) {
	auto appInstance = InstanceTools::getAppInstance( );
	If_Nullptr_Result_Nullptr( appInstance );
	return appInstance->getAppDateTimerManage( );
}
AppDrawManage * InstanceTools::getAppDrawManage( ) {
	auto appUserInterfaceManage = InstanceTools::getAppUserInterfaceManage( );
	If_Nullptr_Result_Nullptr( appUserInterfaceManage );
	return appUserInterfaceManage->getAppDrawManage( );
}
AppInstance * InstanceTools::getAppInstance( ) {
	return AppInstance::getAppInstance( );
}
ApplicationManage * InstanceTools::getApplicationManage( ) {
	auto appInstance = InstanceTools::getAppInstance( );
	If_Nullptr_Result_Nullptr( appInstance );
	return appInstance->getApplicationManage( );
}
AppMenuManage * InstanceTools::getAppMenuManage( ) {
	auto topPtr = InstanceTools::getAppUserInterfaceManage( );
	If_Nullptr_Result_Nullptr( topPtr );
	return topPtr->getAppMenuManage( );
}
AppMusicDecoder * InstanceTools::getAppMusicDecoder( ) {
	auto topPtr = InstanceTools::getAppMusicManage( );
	If_Nullptr_Result_Nullptr( topPtr );
	return topPtr->getAppMusicDecoder( );
}
AppMusicManage * InstanceTools::getAppMusicManage( ) {
	auto topPtr = InstanceTools::getAppDataManage( );
	If_Nullptr_Result_Nullptr( topPtr );
	return topPtr->getAppMusicManage( );
}
AppRenderImage * InstanceTools::getAppRenderImage( ) {
	auto topPtr = InstanceTools::getAppDrawManage( );
	If_Nullptr_Result_Nullptr( topPtr );
	return topPtr->getAppRenderImage( );
}
AppTranslate * InstanceTools::getAppTranslate( ) {
	auto topPtr = InstanceTools::getAppDataManage( );
	If_Nullptr_Result_Nullptr( topPtr );
	return topPtr->getTranslate( );
}
AppUserInterfaceManage * InstanceTools::getAppUserInterfaceManage( ) {
	auto topPtr = InstanceTools::getAppInstance( );
	If_Nullptr_Result_Nullptr( topPtr );
	return topPtr->getAppUserInterfaceManage( );
}
