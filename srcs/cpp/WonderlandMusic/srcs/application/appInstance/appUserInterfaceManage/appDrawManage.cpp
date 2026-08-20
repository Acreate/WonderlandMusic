#include "appDrawManage.h"

#include <QPainter>
#include <QDebug>

#include "../appDataManage.h"

#include "../../../component/musicWindow/interface/item/iMusicFavoriteItem.h"
#include "../../../component/musicWindow/interface/item/iMusicItem.h"

#include "../../../head/after_init_macro.h"
#include "../../../head/before_init_macro.h"
#include "../../../head/init_macro.h"
#include "../../../head/q_debug_message_var_out.h"
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
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "AppDataManage * 获取失败" ) );
	MusicItemWidthInfo *musicItemWidthInfo = appDataManage->getMusicItemWidthInfo( );
	if( musicItemWidthInfo == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appDataManage, getMusicItemWidthInfo, QObject::tr( "MusicItemWidthInfo * 获取失败" ) );
	return drawItem( painter, music_item, musicItemWidthInfo, pos_x, pos_y );
}
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const int &pos_x, const int &pos_y ) const {
	AppDataManage *appDataManage = InstanceTools::getAppDataManage( );
	if( appDataManage == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "AppDataManage * 获取失败" ) );
	MusicItemWidthInfo *musicItemWidthInfo = appDataManage->getMusicItemWidthInfo( );
	if( musicItemWidthInfo == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appDataManage, getMusicItemWidthInfo, QObject::tr( "MusicItemWidthInfo * 获取失败" ) );
	return drawItem( painter, music_item_vector, musicItemWidthInfo, pos_x, pos_y );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item ) const {
	return drawItem( painter, music_favorite_item, 0, 0 );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item, const int &pos_x, const int &pos_y ) const {
	QString musicFavoriteName;
	if( music_favorite_item->getName( musicFavoriteName ) == false )
		return false;
	QFontMetrics fontMetrics = painter.fontMetrics( );
	int horizontalAdvance = fontMetrics.horizontalAdvance( musicFavoriteName );
	int height = fontMetrics.height( );
	painter.drawText( QRect( pos_x, pos_y, horizontalAdvance, height ), musicFavoriteName );
	return true;
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicItem *music_item ) const {
	return drawItem( painter, music_item, 0, 0 );
}
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector ) const {
	return drawItem( painter, music_item_vector, 0, 0 );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info ) const {
	return drawItem( painter, music_item, music_item_width_info, 0, 0 );
}
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info ) const {
	return drawItem( painter, music_item_vector, music_item_width_info, 0, 0 );
}

bool AppDrawManage::drawItem( QPainter &painter, const IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y ) const {
	size_t idCode;
	if( music_item->getIdCode( idCode ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_item, getIdCode, QObject::tr( "获取歌曲id失败" ) );
	QString name;
	if( music_item->getName( name ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_item, getName, QObject::tr( "获取歌曲名称失败" ) );
	QString singer;
	if( music_item->getSinger( singer ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_item, getSinger, QObject::tr( "获取歌曲歌手失败" ) );
	QString elapsedTimeString;
	if( music_item->getElapsedTimeString( elapsedTimeString ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, music_item, getElapsedTimeString, QObject::tr( "获取时间字符串失败" ) );

	QFontMetrics fontMetrics = painter.fontMetrics( );
	const int calculateMinHeight = fontMetrics.height( );

	const int separatorWidth = music_item_width_info->getSeparatorWidth( );
	int intervalWidth = music_item_width_info->getIntervalWidth( ) + pos_x;
	QColor fillSeparatorColor( 255, 255, 255, 255 );
	QRect fillRect = QRect( intervalWidth, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	intervalWidth = intervalWidth + separatorWidth;
	QString text = QString::number( idCode );
	int musicCodeWidth = music_item_width_info->getMusicCodeWidth( );
	QRect codeRect = QRect( intervalWidth, pos_y, musicCodeWidth, calculateMinHeight );
	painter.drawText( codeRect, text );

	intervalWidth = intervalWidth + musicCodeWidth;
	fillRect = QRect( intervalWidth, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	intervalWidth = intervalWidth + separatorWidth;
	int musicNameWidth = music_item_width_info->getMusicNameWidth( );
	QRect nameRect( intervalWidth, pos_y, musicNameWidth, calculateMinHeight );
	painter.drawText( nameRect, name );

	intervalWidth = intervalWidth + musicNameWidth;
	fillRect = QRect( intervalWidth, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	intervalWidth = intervalWidth + separatorWidth;
	int musicSingerNameWidth = music_item_width_info->getMusicSingerNameWidth( );
	QRect singerRect( intervalWidth, pos_y, musicSingerNameWidth, calculateMinHeight );
	painter.drawText( singerRect, singer );

	intervalWidth = intervalWidth + musicSingerNameWidth;
	fillRect = QRect( intervalWidth, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	intervalWidth = intervalWidth + separatorWidth;
	int musicDurationTimeWidth = music_item_width_info->getMusicDurationTimeWidth( );
	QRect elapsedTimeRect( intervalWidth, pos_y, musicDurationTimeWidth, calculateMinHeight );
	painter.drawText( elapsedTimeRect, elapsedTimeString );

	intervalWidth = intervalWidth + musicDurationTimeWidth;
	fillRect = QRect( intervalWidth, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );
	
	Q_Debug_Var_Nmae_MessageString( fillRect );
	return true;
}
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y ) const {
	size_t count = music_item_vector.size( );
	if( count == 0 )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "序列数量为 0" ) );

	auto data = music_item_vector.data( );
	auto fontMetrics = painter.fontMetrics( );
	int height = fontMetrics.height( );
	size_t index = 0;
	int offsetY = 0;
	for( ; index < count; index += 1 ) {
		if( drawItem( painter, data[ index ], music_item_width_info, 0, offsetY ) == false ) {
			QString name;
			data[ index ]->getName( name );
			return Result_Var_Function_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "绘制异常 : music_item_vector[%1].name = %2" ).arg( index ).arg( name ) );
		}
		offsetY += height;
	}
	return true;
}
