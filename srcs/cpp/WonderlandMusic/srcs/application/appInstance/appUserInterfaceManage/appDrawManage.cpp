#include "appDrawManage.h"

#include <QDebug>
#include <QPainter>

#include <component/musicWindow/interface/info/iMusicItemWidthInfo.h>
#include <component/musicWindow/interface/item/iMusicFavoriteItem.h>
#include <component/musicWindow/interface/item/iMusicItem.h>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/init_macro.h>
#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <tools/instanceTools.h>

#include "../appDataManage.h"

#include "../appDataManage/translate/musicTitleWidgetTranslate.h"

#include "appDrawManage/appRenderImage.h"

namespace appDrawTools {
	static bool drawItem( QPainter &painter, const IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info, const int &offset_pos_x, const int &offset_pos_y );
}

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
bool AppDrawManage::drawTitle( QPainter &painter, const IMusicItemWidthInfo *music_item_width_info, int offset_pos_x, int offset_pos_y ) const {
	if( music_item_width_info == nullptr )
		return false;
	if( AppTranslateTools::getMusicTitleWidget( [&painter, music_item_width_info, offset_pos_y, offset_pos_x] ( MusicTitleWidgetTranslate &translate ) {
		QFontMetrics fontMetrics = painter.fontMetrics( );
		const int calculateMinHeight = fontMetrics.height( );

		const int separatorWidth = music_item_width_info->getSeparatorWidth( );
		int intervalwidth = music_item_width_info->getIntervalWidth( );
		int currentX = intervalwidth + offset_pos_x;

		QColor fillSeparatorColor = painter.brush( ).color( );
		QRect fillRect = QRect( currentX, offset_pos_y, separatorWidth, calculateMinHeight );
		painter.fillRect( fillRect, fillSeparatorColor );

		currentX = currentX + separatorWidth + intervalwidth;
		int musicCodeWidth = music_item_width_info->getMusicCodeWidth( );
		QRect codeRect = QRect( currentX, offset_pos_y, musicCodeWidth, calculateMinHeight );
		painter.drawText( codeRect, translate.getMusicCode( ) );

		currentX = currentX + musicCodeWidth + intervalwidth;
		fillRect = QRect( currentX, offset_pos_y, separatorWidth, calculateMinHeight );
		painter.fillRect( fillRect, fillSeparatorColor );

		currentX = currentX + separatorWidth + intervalwidth;
		int musicNameWidth = music_item_width_info->getMusicNameWidth( );
		QRect nameRect( currentX, offset_pos_y, musicNameWidth, calculateMinHeight );
		painter.drawText( nameRect, translate.getMusicName( ) );

		currentX = currentX + musicNameWidth + intervalwidth;
		fillRect = QRect( currentX, offset_pos_y, separatorWidth, calculateMinHeight );
		painter.fillRect( fillRect, fillSeparatorColor );

		currentX = currentX + separatorWidth + intervalwidth;
		int musicSingerNameWidth = music_item_width_info->getMusicSingerNameWidth( );
		QRect singerRect( currentX, offset_pos_y, musicSingerNameWidth, calculateMinHeight );
		painter.drawText( singerRect, translate.getMusicSingeName( ) );

		currentX = currentX + musicSingerNameWidth + intervalwidth;
		fillRect = QRect( currentX, offset_pos_y, separatorWidth, calculateMinHeight );
		painter.fillRect( fillRect, fillSeparatorColor );

		currentX = currentX + separatorWidth + intervalwidth;
		int musicDurationTimeWidth = music_item_width_info->getMusicDurationTimeWidth( );
		QRect elapsedTimeRect( currentX, offset_pos_y, musicDurationTimeWidth, calculateMinHeight );
		painter.drawText( elapsedTimeRect, translate.getMusicDurationTime( ) );

		currentX = currentX + musicDurationTimeWidth + intervalwidth;
		fillRect = QRect( currentX, offset_pos_y, separatorWidth, calculateMinHeight );
		painter.fillRect( fillRect, fillSeparatorColor );

		return true;
	} ) == false )
		return false;
	return true;
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicItem *music_item, const int &offset_pos_x, const int &offset_pos_y ) const {
	AppDataManage *appDataManage = InstanceTools::getAppDataManage( );
	if( appDataManage == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "AppDataManage * 获取失败" ) );
	auto musicItemWidthInfo = appDataManage->getMusicItemWidthInfo( );
	if( musicItemWidthInfo == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appDataManage, getMusicItemWidthInfo, QObject::tr( "MusicItemWidthInfo * 获取失败" ) );
	return drawItem( painter, music_item, musicItemWidthInfo, offset_pos_x, offset_pos_y );
}
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const int &offset_pos_x, const int &offset_pos_y ) const {
	AppDataManage *appDataManage = InstanceTools::getAppDataManage( );
	if( appDataManage == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "AppDataManage * 获取失败" ) );
	auto musicItemWidthInfo = appDataManage->getMusicItemWidthInfo( );
	if( musicItemWidthInfo == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appDataManage, getMusicItemWidthInfo, QObject::tr( "MusicItemWidthInfo * 获取失败" ) );
	return drawItem( painter, music_item_vector, musicItemWidthInfo, offset_pos_x, offset_pos_y );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item ) const {
	return drawItem( painter, music_favorite_item, 0, 0 );
}
bool AppDrawManage::drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item, const int &offset_pos_x, const int &offset_pos_y ) const {
	QString musicFavoriteName;
	if( music_favorite_item->getName( musicFavoriteName ) == false )
		return false;
	QFontMetrics fontMetrics = painter.fontMetrics( );
	int horizontalAdvance = fontMetrics.horizontalAdvance( musicFavoriteName );
	int height = fontMetrics.height( );
	painter.drawText( QRect( offset_pos_x, offset_pos_y, horizontalAdvance, height ), musicFavoriteName );
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

bool appDrawTools::drawItem( QPainter &painter, const IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info, const int &offset_pos_x, const int &offset_pos_y ) {
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

	const int calculateMinHeight = music_item_width_info->getSuggestHeight( );

	const int separatorWidth = music_item_width_info->getSeparatorWidth( );
	int intervalWidth = music_item_width_info->getIntervalWidth( );
	intervalWidth *= 2;
	int drawItemWidth = intervalWidth + separatorWidth;
	int currentX = drawItemWidth;
	QString text = QString::number( idCode );
	int musicCodeWidth = music_item_width_info->getMusicCodeWidth( );
	QRect codeRect = QRect( currentX, offset_pos_y, musicCodeWidth, calculateMinHeight );
	painter.drawText( codeRect, text );

	currentX = currentX + musicCodeWidth + drawItemWidth;
	int musicNameWidth = music_item_width_info->getMusicNameWidth( );
	QRect nameRect( currentX, offset_pos_y, musicNameWidth, calculateMinHeight );
	painter.drawText( nameRect, name );

	currentX = currentX + musicNameWidth + drawItemWidth;
	int musicSingerNameWidth = music_item_width_info->getMusicSingerNameWidth( );
	QRect singerRect( currentX, offset_pos_y, musicSingerNameWidth, calculateMinHeight );
	painter.drawText( singerRect, singer );

	currentX = currentX + musicSingerNameWidth + drawItemWidth;
	int musicDurationTimeWidth = music_item_width_info->getMusicDurationTimeWidth( );
	QRect elapsedTimeRect( currentX, offset_pos_y, musicDurationTimeWidth, calculateMinHeight );
	painter.drawText( elapsedTimeRect, elapsedTimeString );

	return true;
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
	int intervalWidth = music_item_width_info->getIntervalWidth( );
	int currentX = intervalWidth + pos_x;
	QColor fillSeparatorColor = painter.brush( ).color( );;
	QRect fillRect = QRect( currentX, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	currentX = currentX + separatorWidth;
	QString text = QString::number( idCode );
	int musicCodeWidth = music_item_width_info->getMusicCodeWidth( );
	QRect codeRect = QRect( currentX, pos_y, musicCodeWidth, calculateMinHeight );
	painter.drawText( codeRect, text );

	currentX = currentX + musicCodeWidth + intervalWidth;
	fillRect = QRect( currentX, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	currentX = currentX + separatorWidth + intervalWidth;
	int musicNameWidth = music_item_width_info->getMusicNameWidth( );
	QRect nameRect( currentX, pos_y, musicNameWidth, calculateMinHeight );
	painter.drawText( nameRect, name );

	currentX = currentX + musicNameWidth + intervalWidth;
	fillRect = QRect( currentX, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	currentX = currentX + separatorWidth + intervalWidth;
	int musicSingerNameWidth = music_item_width_info->getMusicSingerNameWidth( );
	QRect singerRect( currentX, pos_y, musicSingerNameWidth, calculateMinHeight );
	painter.drawText( singerRect, singer );

	currentX = currentX + musicSingerNameWidth + intervalWidth;
	fillRect = QRect( currentX, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	currentX = currentX + separatorWidth + intervalWidth;
	int musicDurationTimeWidth = music_item_width_info->getMusicDurationTimeWidth( );
	QRect elapsedTimeRect( currentX, pos_y, musicDurationTimeWidth, calculateMinHeight );
	painter.drawText( elapsedTimeRect, elapsedTimeString );

	currentX = currentX + musicDurationTimeWidth + intervalWidth;
	fillRect = QRect( currentX, pos_y, separatorWidth, calculateMinHeight );
	painter.fillRect( fillRect, fillSeparatorColor );

	return true;
}
bool AppDrawManage::drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y ) const {
	size_t count = music_item_vector.size( );
	if( count == 0 )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "序列数量为 0" ) );

	auto data = music_item_vector.data( );
	auto fontMetrics = painter.fontMetrics( );
	int height = music_item_width_info->getSuggestHeight( );
	size_t index = 0;
	int offsetY = 0;
	for( ; index < count; index += 1 ) {
		if( appDrawTools::drawItem( painter, data[ index ], music_item_width_info, 0, offsetY ) == false ) {
			QString name;
			data[ index ]->getName( name );
			return Result_Var_Function_Messag_Ptr_Out_Args( false, this, drawItem, QObject::tr( "绘制异常 : music_item_vector[%1].name = %2" ).arg( index ).arg( name ) );
		}
		offsetY += height;
	}

	const int separatorWidth = music_item_width_info->getSeparatorWidth( );
	int intervalWidth = music_item_width_info->getIntervalWidth( );
	int currentX = intervalWidth + pos_x;
	QColor fillSeparatorColor = painter.brush( ).color( );
	QRect fillRect = QRect( currentX, pos_y, separatorWidth, offsetY );
	painter.fillRect( fillRect, fillSeparatorColor );

	int musicCodeWidth = music_item_width_info->getMusicCodeWidth( );
	currentX = currentX + separatorWidth + musicCodeWidth + intervalWidth;
	fillRect = QRect( currentX, pos_y, separatorWidth, offsetY );
	painter.fillRect( fillRect, fillSeparatorColor );

	int musicNameWidth = music_item_width_info->getMusicNameWidth( );
	currentX = currentX + separatorWidth + musicNameWidth + intervalWidth;
	fillRect = QRect( currentX, pos_y, separatorWidth, offsetY );
	painter.fillRect( fillRect, fillSeparatorColor );

	int musicSingerNameWidth = music_item_width_info->getMusicSingerNameWidth( );
	currentX = currentX + separatorWidth + musicSingerNameWidth + intervalWidth;
	fillRect = QRect( currentX, pos_y, separatorWidth, offsetY );
	painter.fillRect( fillRect, fillSeparatorColor );

	int musicDurationTimeWidth = music_item_width_info->getMusicDurationTimeWidth( );
	currentX = currentX + separatorWidth + musicDurationTimeWidth + intervalWidth;
	fillRect = QRect( currentX, pos_y, separatorWidth, offsetY );
	painter.fillRect( fillRect, fillSeparatorColor );

	return true;
}
