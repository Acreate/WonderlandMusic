#include "musicManage.h"

#include "musicDecoder.h"

MusicManage::~MusicManage( ) {
}

bool MusicManage::deleteResource( ) {
	delete_ptr( musicDecoder );
	return true;
}

bool MusicManage::init( ) {
	deleteResource( );
	if( make_ptr( musicDecoder ) == nullptr )
		return false;
	if( musicDecoder->init( ) == false )
		return false;
	return true;
}

MusicDecoder * MusicManage::getMusicDecoder( ) const {
	return musicDecoder;
}
