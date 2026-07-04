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

	Before_Init_Resource_App_Core_Ptr( appRenderImage );

	Init_Resource_App_Core_Ptr( appRenderImage );

	After_Init_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

bool AppDrawManage::initBefore( ) {
	return true;
}

bool AppDrawManage::initAfter( ) {
	return true;
}

AppRenderImage * AppDrawManage::getAppRenderImage( ) const {
	return appRenderImage;
}
