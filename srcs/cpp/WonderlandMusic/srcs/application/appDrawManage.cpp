#include "appDrawManage.h"

#include "renderImage.h"

#include "../tools/templateArgs.h"

AppDrawManage::~AppDrawManage( ) {
	deleteResource( );
}

bool AppDrawManage::deleteResource( ) {
	if( TemplateArgs::delete_ptr( renderImage ) == false )
		return false;
	return true;
}

bool AppDrawManage::init( ) {
	deleteResource( );
	if( TemplateArgs::make_ptr( renderImage ) == nullptr )
		return false;
	if( init_app_core_ptr( renderImage ) == false )
		return false;
	return true;
}

RenderImage * AppDrawManage::getRenderImage( ) const {
	return renderImage;
}
