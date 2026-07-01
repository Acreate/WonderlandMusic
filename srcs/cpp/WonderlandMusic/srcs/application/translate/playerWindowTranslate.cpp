#include "playerWindowTranslate.h"

bool PlayerWindowTranslate::init( ) {
	loadDiskFileTitle = QObject::tr( "加载多个文件" );
	loadDiskDirTitle = QObject::tr( "加载多个目录" );
	musicTypeName = QObject::tr( "音频类型" );
	anyTypeName = QObject::tr( "所有类型" );
	return true;
}

PlayerWindowTranslate::~PlayerWindowTranslate( ) {
}

const QString & PlayerWindowTranslate::getLoadDiskFileTitle( ) const {
	return loadDiskFileTitle;
}

const QString & PlayerWindowTranslate::getLoadDiskDirTitle( ) const {
	return loadDiskDirTitle;
}

const QString & PlayerWindowTranslate::getMusicTypeName( ) const {
	return musicTypeName;
}

const QString & PlayerWindowTranslate::getAnyTypeName( ) const {
	return anyTypeName;
}
