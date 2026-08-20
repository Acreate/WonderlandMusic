#include "appDrawManage.h"

#include <QPainter>

#include "../appDataManage.h"

#include "../../../component/musicWindow/interface/item/iMusicFavoriteItem.h"

#include "../../../head/after_init_macro.h"
#include "../../../head/before_init_macro.h"
#include "../../../head/init_macro.h"
#include "../../../head/release_macro.h"
#include "../../../head/result_message_out.h"

#include "../../../info/musicItemWidthInfo.h"

#include "../../../tools/instanceTools.h"

#include "appDrawManage/appRenderImage.h"

AppDrawManage::~AppDrawManage( ) {
	deleteResource( );
}

bool AppDrawManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

bool AppDrawManage::init( ) {
	Init_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

bool AppDrawManage::initBefore( ) {
	deleteResource( );
	appRenderImage = new AppRenderImage;

	Before_Init_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

bool AppDrawManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appRenderImage );
	return true;
}

AppRenderImage * AppDrawManage::getAppRenderImage( ) const {
	return appRenderImage;
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicItem *music_item, const int &pos_x, const int &pos_y ) const {
	AppDataManage *appDataManage = InstanceTools::getAppDataManage( );
	if( appDataManage == nullptr )
		return Result_Var_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "AppDataManage * 获取失败" ) );
	MusicItemWidthInfo *musicItemWidthInfo = appDataManage->getMusicItemWidthInfo( );
	if( musicItemWidthInfo == nullptr )
		return Result_Var_Messag_Ptr_Out_Args( false, appDataManage, getMusicItemWidthInfo, QObject::tr( "MusicItemWidthInfo * 获取失败" ) );
	return drawItem( painter, music_item, musicItemWidthInfo, pos_x, pos_y );
}
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const int &pos_x, const int &pos_y ) const {
	AppDataManage *appDataManage = InstanceTools::getAppDataManage( );
	if( appDataManage == nullptr )
		return Result_Var_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "AppDataManage * 获取失败" ) );
	MusicItemWidthInfo *musicItemWidthInfo = appDataManage->getMusicItemWidthInfo( );
	if( musicItemWidthInfo == nullptr )
		return Result_Var_Messag_Ptr_Out_Args( false, appDataManage, getMusicItemWidthInfo, QObject::tr( "MusicItemWidthInfo * 获取失败" ) );
	return drawItem( painter, music_item_vector, musicItemWidthInfo, pos_x, pos_y );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item ) const {
	return drawItem( painter, music_favorite_item, 0, 0 );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item, const int &pos_x, const int &pos_y ) const {
	auto font = appRenderImage->getFont( );
	return drawItem( painter, music_favorite_item, *font, pos_x, pos_y );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicItem *music_item ) const {
	return drawItem( painter, music_item, 0, 0 );
}
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector ) const {
	return drawItem( painter, music_item_vector, 0, 0 );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item, const QFont &font, const int &pos_x, const int &pos_y ) const {
	QFontMetrics fontMetrics( font );
	QString musicFavoriteName;
	if( music_favorite_item->getName( musicFavoriteName ) == false )
		return false;
	int horizontalAdvance = fontMetrics.horizontalAdvance( musicFavoriteName );
	int height = fontMetrics.height( );
	painter.setFont( font );
	painter.drawText( QRect( pos_x, horizontalAdvance, pos_y, height ), musicFavoriteName );
	return true;
}
// todo : 实现
bool AppDrawManage::drawItem( QPainter &painter, const IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y ) const {
	return false;
}
// todo : 实现
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y ) const {
	return false;
}
// todo : 实现
bool AppDrawManage::drawItem( QPainter &painter, const IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info ) const {
	return false;
}
// todo : 实现
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info ) const {
	return false;
}
