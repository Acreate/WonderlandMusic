#include "playerListWidgetTranslate.h"

#include <QObject>

bool PlayerListWidgetTranslate::init( ) {
	removeDiskFileError = QObject::tr( "删除磁盘文件失败" );
	removeListMusicItemError = QObject::tr( "删除列表音乐项失败" );
	musicTypeName = QObject::tr( "音频类型" );
	anyTypeName = QObject::tr( "所有类型" );

	loadDiskFileTitle = QObject::tr( "加载多个文件" );
	loadDiskDirTitle = QObject::tr( "加载多个目录" );
	return true;
}

const QString & PlayerListWidgetTranslate::getRemoveDiskFileError( ) const {
	return removeDiskFileError;
}

const QString & PlayerListWidgetTranslate::getRemoveListMusicItemError( ) const {
	return removeListMusicItemError;
}

const QString & PlayerListWidgetTranslate::getMusicTypeName( ) const {
	return musicTypeName;
}

const QString & PlayerListWidgetTranslate::getAnyTypeName( ) const {
	return anyTypeName;
}

const QString & PlayerListWidgetTranslate::getLoadDiskFileTitle( ) const {
	return loadDiskFileTitle;
}

const QString & PlayerListWidgetTranslate::getLoadDiskDirTitle( ) const {
	return loadDiskDirTitle;
}
