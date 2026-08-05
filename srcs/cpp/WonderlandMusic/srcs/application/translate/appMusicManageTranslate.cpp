#include "appMusicManageTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/appTranslateTools.h>

Defininition_Get_Translate( AppMusicManage );
bool AppMusicManageTranslate::init( ) {
	rootFavoriteName = QObject::tr( "默认" );
	anyFileTypeName = QObject::tr( "任意" );
	musicFileTypeName = QObject::tr( "音频" );
	selectMultipleFileTitle = QObject::tr( "多选文件" );
	selectMultipleDirTitle = QObject::tr( "多选目录" );
	return true;
}

const QString & AppMusicManageTranslate::getRootFavoriteName( ) const {
	return rootFavoriteName;
}

const QString & AppMusicManageTranslate::getAnyFileTypeName( ) const {
	return anyFileTypeName;
}

const QString & AppMusicManageTranslate::getMusicFileTypeName( ) const {
	return musicFileTypeName;
}

const QString & AppMusicManageTranslate::getSelectMultipleFileTitle( ) const {
	return selectMultipleFileTitle;
}

const QString & AppMusicManageTranslate::getSelectMultipleDirTitle( ) const {
	return selectMultipleDirTitle;
}
