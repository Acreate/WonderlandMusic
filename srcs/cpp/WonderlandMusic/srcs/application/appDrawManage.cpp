#include "appDrawManage.h"

#include "appRenderImage.h"

AppDrawManage::~AppDrawManage( ) {
	deleteResource( );
}

bool AppDrawManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

bool AppDrawManage::init( ) {
	deleteResource( );
	appRenderImage = new AppRenderImage;
	Init_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

AppRenderImage * AppDrawManage::getAppRenderImage( ) const {
	return appRenderImage;
}
