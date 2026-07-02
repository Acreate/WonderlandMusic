#include "playerListWidgetTranslate.h"

#include <QObject>

bool PlayerListWidgetTranslate::init( ) {
	removeDiskFileError = QObject::tr( "删除磁盘文件失败" );
	removeListMusicItemError = QObject::tr( "删除列表音乐项失败" );

	return true;
}

const QString & PlayerListWidgetTranslate::getRemoveDiskFileError( ) const {
	return removeDiskFileError;
}

const QString & PlayerListWidgetTranslate::getRemoveListMusicItemError( ) const {
	return removeListMusicItemError;
}
