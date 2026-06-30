#include "musicManage.h"

#include "musicDecoder.h"

MusicManage::~MusicManage( ) {
}

bool MusicManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( musicDecoder );
	return true;
}

bool MusicManage::init( ) {
	deleteResource( );
	musicDecoder = new MusicDecoder;

	Init_Resource_App_Core_Ptr( musicDecoder );
	return true;
}

MusicDecoder * MusicManage::getMusicDecoder( ) const {
	return musicDecoder;
}
