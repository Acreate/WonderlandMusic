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
	Init_Resource_App_Core_Ptr( appRenderImage );

	return true;
}

bool AppDrawManage::initBefore( ) {
	deleteResource( );
	appRenderImage = new AppRenderImage;

	Before_Init_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

bool AppDrawManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

AppRenderImage * AppDrawManage::getAppRenderImage( ) const {
	return appRenderImage;
}
