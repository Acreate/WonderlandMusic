#include "appDrawManage.h"

#include "renderImage.h"

#include "../tools/templateArgs.h"

AppDrawManage::~AppDrawManage( ) {
	deleteResource( );
}

bool AppDrawManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( renderImage );
	return true;
}

bool AppDrawManage::init( ) {
	deleteResource( );
	renderImage = new RenderImage;
	Init_Resource_App_Core_Ptr( renderImage );
	return true;
}

RenderImage * AppDrawManage::getRenderImage( ) const {
	return renderImage;
}
