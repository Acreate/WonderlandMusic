#include "musicManage.h"

#include "musicDecoder.h"

#include "../tools/templateArgs.h"

MusicManage::~MusicManage( ) {
}

bool MusicManage::deleteResource( ) {
	TemplateArgs::delete_ptr( musicDecoder );
	return true;
}

bool MusicManage::init( ) {
	deleteResource( );
	if( TemplateArgs::make_ptr( musicDecoder ) == nullptr )
		return false;
	if( musicDecoder->init( ) == false )
		return false;
	return true;
}

MusicDecoder * MusicManage::getMusicDecoder( ) const {
	return musicDecoder;
}
