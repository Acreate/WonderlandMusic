#include "musicFavoriteMenuTranslate.h"
#include "../appTranslate.h"

#include "../../head/defininition_get_translate.h"

#include "../../tools/appTranslateTools.h"
Defininition_Get_Translate( MusicFavoriteMenu );
bool MusicFavoriteMenuTranslate::init( ) {
	createFavoriteItem = QObject::tr( "新建收藏夹..." );
	renameFavoriteItem = QObject::tr( "重命名收藏夹[%1]" );
	deleteFavoriteItem = QObject::tr( "删除收藏夹[%1]" );
	addMusicFileToFavoriteItem = QObject::tr( "添加音频文件到收藏夹[%1]" );
	addMusicDirToFavoriteItem = QObject::tr( "添加音频目录到收藏夹[%1]" );

	illegalRenameFavoriteItem = QObject::tr( "非法重命令" );
	illegalDeleteFavoriteItem = QObject::tr( "非法删除" );
	illegalAddMusicFileToFavoriteItem = QObject::tr( "非法添加文件" );
	illegalAddMusicDirToFavoriteItem = QObject::tr( "非法添加目录" );
	return true;
}
const QString & MusicFavoriteMenuTranslate::getCreateFavoriteItem( ) const {
	return createFavoriteItem;
}
const QString & MusicFavoriteMenuTranslate::getIllegalRenameFavoriteItem( ) const {
	return illegalRenameFavoriteItem;
}
const QString & MusicFavoriteMenuTranslate::getIllegalDeleteFavoriteItem( ) const {
	return illegalDeleteFavoriteItem;
}
const QString & MusicFavoriteMenuTranslate::getIllegalAddMusicFileToFavoriteItem( ) const {
	return illegalAddMusicFileToFavoriteItem;
}
const QString & MusicFavoriteMenuTranslate::getIllegalAddMusicDirToFavoriteItem( ) const {
	return illegalAddMusicDirToFavoriteItem;
}
const QString & MusicFavoriteMenuTranslate::getRenameFavoriteItem( ) const {
	return renameFavoriteItem;
}
const QString & MusicFavoriteMenuTranslate::getDeleteFavoriteItem( ) const {
	return deleteFavoriteItem;
}
const QString & MusicFavoriteMenuTranslate::getAddMusicFileToFavoriteItem( ) const {
	return addMusicFileToFavoriteItem;
}
const QString & MusicFavoriteMenuTranslate::getAddMusicDirToFavoriteItem( ) const {
	return addMusicDirToFavoriteItem;
}
