#include "appMusicManage.h"

#include <QPainter>

#include <head/init_macro.h>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>

#include "../../../component/musicWindow/interface/info/iMusicItemWidthInfo.h"
#include "../../../component/musicWindow/interface/item/iMusicItem.h"

#include "../../../head/release_macro.h"
#include "../../../head/result_message_out.h"

#include "../../../item/musicInfoItem.h"

#include "../../../mutex/userMutex.h"

#include "../../../tools/instanceTools.h"
#include "../../../tools/pathTools.h"

#include "../appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "appMusicManage/appMusicDecoder.h"

bool AppMusicManage::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	Delete_Resource_App_Core_Ptr( appMusicDecoder );
	Delete_Resource_App_Core_Ptr( musicItemWidthInfo );
	auto clearMusicItemVectorResult = unsafeClearMusicItemVector( );
	auto clearMusicFavoriteItemResult = unsafeClearMusicFavoriteItem( );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return clearMusicItemVectorResult && clearMusicFavoriteItemResult;
}
bool AppMusicManage::unsafeClearMusicItemVector( ) {
	return false;
}
bool AppMusicManage::unsafeClearMusicFavoriteItem( ) {
	return false;
}
bool AppMusicManage::renderImage( QPainter &painter, int intervalWidth, size_t index, IMusicItem *music_item, int calculate_min_width, int calculate_height, const QFont &font, const QColor &fill_separator_color ) const {
	size_t idCode;
	if( music_item->getIdCode( idCode ) == false )
		return false;
	QString name;
	if( music_item->getName( name ) == false )
		return false;
	QString singer;
	if( music_item->getSinger( singer ) == false )
		return false;
	QString elapsedTimeString;
	if( music_item->getElapsedTimeString( elapsedTimeString ) == false )
		return false;
	auto buff = music_item->createResizeBuff( calculate_min_width, calculate_height );
	if( buff == nullptr )
		return false;
	buff->fill( 0 );
	painter.begin( buff );
	painter.setFont( font );
	int separatorWidth = this->musicItemWidthInfo->getSeparatorWidth( );
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;

	QString text = QString::number( idCode );
	int musicCodeWidth = this->musicItemWidthInfo->getMusicCodeWidth( );
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), text );

	intervalWidth += intervalWidth + musicCodeWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), name );

	int musicNameWidth = this->musicItemWidthInfo->getMusicNameWidth( );
	intervalWidth += intervalWidth + musicNameWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), singer );

	int musicSingerNameWidth = this->musicItemWidthInfo->getMusicSingerNameWidth( );
	intervalWidth += intervalWidth + musicSingerNameWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), elapsedTimeString );

	int musicDurationTimeWidth = this->musicItemWidthInfo->getMusicDurationTimeWidth( );
	intervalWidth += intervalWidth + musicDurationTimeWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	painter.end( );
	return true;
}
bool AppMusicManage::renderImage( size_t index, IMusicItem *music_item ) const {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	auto fontMetrics = appRenderImage->getFontMetrics( );
	int fontHeight = fontMetrics->height( );
	QPainter painter;

	QColor fillSeparatorColor = QColor( 255, 255, 255 );
	auto calculateMinWidth = musicItemWidthInfo->getCalculateMinWidth( );
	auto font = appRenderImage->getFont( );
	int intervalWidth = musicItemWidthInfo->getIntervalWidth( );
	return renderImage( painter, intervalWidth, index, music_item, calculateMinWidth, fontHeight, *font, fillSeparatorColor );
}

bool AppMusicManage::init( ) {
	Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

bool AppMusicManage::initBefore( ) {
	deleteResource( );
	appMusicDecoder = new AppMusicDecoder;
	Before_Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

bool AppMusicManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

AppMusicDecoder * AppMusicManage::getAppMusicDecoder( ) const {
	return appMusicDecoder;
}
size_t AppMusicManage::loadMusicFile( const std::vector< QString > &music_file_path_vector ) {
	size_t result = 0;
	size_t count = music_file_path_vector.size( );
	if( count == 0 )
		return result;
	size_t index = 0;
	auto data = music_file_path_vector.data( );
	for( ; index < count; index += 1 )
		result += loadMusicFile( data[ index ] );
	return result;
}
size_t AppMusicManage::loadMusicFile( const std::list< QString > &music_file_path_list ) {
	size_t result = 0;
	auto iterator = music_file_path_list.begin( );
	auto end = music_file_path_list.end( );
	if( iterator == end )
		return result;
	for( ; iterator != end; ++iterator )
		result += loadMusicFile( *iterator );
	return result;
}
size_t AppMusicManage::loadMusicFile( const QStringList &music_file_path_list ) {
	size_t result = 0;
	size_t count = music_file_path_list.size( );
	if( count == 0 )
		return result;
	size_t index = 0;
	auto data = music_file_path_list.data( );
	for( ; index < count; index += 1 )
		result += loadMusicFile( data[ index ] );
	return result;
}
size_t AppMusicManage::loadMusicFile( const QString &music_file_path ) {
	QFileInfo info( music_file_path );
	if( info.exists( ) == false )
		return 0;
	auto absoluteFilePath = info.absoluteFilePath( );
	if( PathTools::isMusicFile( absoluteFilePath ) == false )
		return 0;
	userMutex->lock( );
	auto musicItem = new MusicInfoItem( this, music_file_path );
	musicItemVector.emplace_back( musicItem );
	userMutex->unlock( );
	return 1;
}
bool AppMusicManage::loadMusicDir( const QString &music_dir_path ) {
	bool result = false;

	QStringList filterMusicFileList;
	QStringList getFileList;
	qsizetype musicFileCount;
	if( PathTools::entryFilePath( filterMusicFileList, music_dir_path ) ) {
		musicFileCount = PathTools::filterFile( getFileList, filterMusicFileList );
		if( musicFileCount ) {
			musicFileCount = PathTools::filterMusicFile( filterMusicFileList, getFileList );
			if( musicFileCount ) {
				auto data = filterMusicFileList.data( );
				qsizetype index;
				userMutex->lock( );
				for( index = 0; index < musicFileCount; index += 1 ) {
					auto musicItem = new MusicInfoItem( this, data[ index ] );
					musicItemVector.emplace_back( musicItem );
				}
				userMutex->unlock( );
				result = true;
			}
		}
	}
	return result;
}
bool AppMusicManage::unsafeClear( ) {
	auto clearMusicItemVectorResult = unsafeClearMusicItemVector( );
	auto clearMusicFavoriteItemResult = unsafeClearMusicFavoriteItem( );
	return clearMusicItemVectorResult && clearMusicFavoriteItemResult;
}
bool AppMusicManage::getMusicWindowInfoJsonData( QJsonObject &result_json_object ) {
	return true;
}
bool AppMusicManage::setMusicWindowInfoJsonData( const QJsonObject &result_json_object ) {
	return true;
}

bool AppMusicManage::hasMusicFile( const QString &file_path ) const {
	return false;
}
bool AppMusicManage::updateMusicItem( IMusicItem *music_item ) {
	return false;
}
bool AppMusicManage::removeMusicItem( IMusicItem *music_item ) {
	return false;
}
bool AppMusicManage::hasMusicItem( size_t &result_index, const IMusicItem *music_item ) const {
	return false;
}

bool AppMusicManage::clear( ) {
	userMutex->lock( );
	auto result = unsafeClear( );
	userMutex->unlock( );
	return result;
}
const IMusicItemWidthInfo & AppMusicManage::getMusicItemWidthInfo( ) const {
	return *musicItemWidthInfo;
}
bool AppMusicManage::setMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) {
	if( musicItemWidthInfo->setIMusicItemWidthInfo( music_item_width_info ) == false )
		return Result_Var_Messag_Ptr_Out_Args( false, musicItemWidthInfo, setIMusicItemWidthInfo, tr( "配置项的宽度信息异常" ) );
	return true;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
