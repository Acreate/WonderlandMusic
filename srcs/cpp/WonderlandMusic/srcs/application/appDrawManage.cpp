#include "appDrawManage.h"

#include "renderImage.h"

#include "../tools/templateArgs.h"

AppDrawManage::~AppDrawManage( ) {
	deleteResource( );
}

bool AppDrawManage::deleteResource( ) {
	if( make_ptr( renderImage ) )
		return false;
	return true;
}

bool AppDrawManage::init( ) {
	deleteResource( );
	if( make_ptr( renderImage ) == nullptr )
		return false;
	if( make_ptr( renderImage ) )
		return false;
	return true;
}

RenderImage * AppDrawManage::getRenderImage( ) const {
	return renderImage;
}
