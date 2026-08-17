#include "appMusicManage.h"
#include <QJsonObject>
#include <QPainter>

#include <head/init_macro.h>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>

#include "../../../component/musicWindow/Item/musicItem/musicItem.h"
#include "../../../component/musicWindow/itemWidthInfo/ItemWidthInfo.h"
#include "../../../component/musicWindow/musicLoad/musicLoad.h"

#include "../../../head/release_macro.h"

#include "../../../mutex/userMutex.h"

#include "../../../tools/instanceTools.h"

#include "../appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "appMusicManage/appMusicDecoder.h"

bool AppMusicManage::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	Delete_Resource_App_Core_Ptr( appMusicDecoder );
	Delete_Resource_App_Core_Ptr( itemWidthInfo );
	Delete_Resource_App_Core_Ptr( musicLoad );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
bool AppMusicManage::renderImage( QPainter &painter, int intervalWidth, size_t index, MusicItem *music_item, int calculate_min_width, int calculate_height, const QFont &font, const QColor &fill_separator_color ) const {
	music_item->idCode = index;
	if( music_item->rendBuff )
		delete music_item->rendBuff;
	music_item->rendBuff = new QImage( calculate_min_width, calculate_height, QImage::Format_RGBA8888 );
	music_item->rendBuff->fill( 0 );
	painter.begin( music_item->rendBuff );
	painter.setFont( font );
	int separatorWidth = this->itemWidthInfo->getSeparatorWidth( );
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;

	QString text = QString::number( music_item->idCode );
	int musicCodeWidth = this->itemWidthInfo->getMusicCodeWidth( );
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), text );

	intervalWidth += intervalWidth + musicCodeWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), music_item->name );

	int musicNameWidth = this->itemWidthInfo->getMusicNameWidth( );
	intervalWidth += intervalWidth + musicNameWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), music_item->singer );

	int musicSingerNameWidth = this->itemWidthInfo->getMusicSingerNameWidth( );
	intervalWidth += intervalWidth + musicSingerNameWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), music_item->elapsedTimeString );

	int musicDurationTimeWidth = this->itemWidthInfo->getMusicDurationTimeWidth( );
	intervalWidth += intervalWidth + musicDurationTimeWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	painter.end( );
	return true;
}
bool AppMusicManage::renderImage( size_t index, MusicItem *music_item ) const {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	auto fontMetrics = appRenderImage->getFontMetrics( );
	int fontHeight = fontMetrics->height( );
	QPainter painter;

	QColor fillSeparatorColor = QColor( 255, 255, 255 );
	auto calculateMinWidth = itemWidthInfo->getCalculateMinWidth( );
	auto font = appRenderImage->getFont( );
	int intervalWidth = itemWidthInfo->getIntervalWidth( );
	return renderImage( painter, intervalWidth, index, music_item, calculateMinWidth, fontHeight, *font, fillSeparatorColor );
}

bool AppMusicManage::init( ) {
	Init_Resource_App_Core_Ptr( appMusicDecoder );
	Init_Resource_App_Core_Ptr( musicLoad );
	return true;
}

bool AppMusicManage::initBefore( ) {
	deleteResource( );
	appMusicDecoder = new AppMusicDecoder;
	musicLoad = new MusicLoad( this );
	itemWidthInfo = new ItemWidthInfo;
	Before_Init_Resource_App_Core_Ptr( appMusicDecoder );
	Before_Init_Resource_App_Core_Ptr( musicLoad );
	return true;
}

bool AppMusicManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appMusicDecoder );
	After_Init_Resource_App_Core_Ptr( musicLoad );
	return true;
}

AppMusicDecoder * AppMusicManage::getAppMusicDecoder( ) const {
	return appMusicDecoder;
}
size_t AppMusicManage::loadMusicFile( const std::vector< QString > &music_file_path_vector ) {
	return musicLoad->loadMusicFile( music_file_path_vector );
}
size_t AppMusicManage::loadMusicFile( const std::list< QString > &music_file_path_list ) {
	return musicLoad->loadMusicFile( music_file_path_list );
}
size_t AppMusicManage::loadMusicFile( const QStringList &music_file_path_list ) {
	return musicLoad->loadMusicFile( music_file_path_list );
}
size_t AppMusicManage::loadMusicFile( const QString &music_file_path ) {
	return musicLoad->loadMusicFile( music_file_path );
}
bool AppMusicManage::loadMusicDir( const QString &music_dir_path ) {
	return musicLoad->loadMusicDir( music_dir_path );
}
bool AppMusicManage::unsafeClear( ) {
	return false;
}
bool AppMusicManage::getMusicWindowInfoJsonData( QJsonObject &result_json_object ) {
	return true;
}
bool AppMusicManage::setMusicWindowInfoJsonData( const QJsonObject &result_json_object ) {
	return true;
}
bool AppMusicManage::removeMusicLoad( MusicLoad *music_load ) {
	return false;
}
bool AppMusicManage::hasMusicFile( const QString &file_path ) const {
	return false;
}
bool AppMusicManage::updateMusicItem( MusicItem *music_item ) {
	return false;
}
bool AppMusicManage::removeMusicItem( MusicItem *music_item ) {
	return false;
}
bool AppMusicManage::hasMusicItem( size_t &result_index, const MusicItem *music_item ) const {
	return false;
}
bool AppMusicManage::addMusicItem( MusicItem *music_item ) {
	return false;
}
bool AppMusicManage::clear( ) {
	userMutex->lock( );
	auto result = unsafeClear( );
	userMutex->unlock( );
	return result;
}
const ItemWidthInfo & AppMusicManage::getItemWidthInfo( ) const {
	return *itemWidthInfo;
}
void AppMusicManage::setItemWidthInfo( const ItemWidthInfo &item_width_info ) {
	*itemWidthInfo = item_width_info;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
