#include "appMusicManage.h"

#include <QPainter>

#include <component/musicWindow/interface/info/iMusicItemWidthInfo.h>
#include <component/musicWindow/interface/item/iMusicItem.h>

#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <mutex/userMutex.h>

#include <tools/pathTools.h>

#include <musicImpement/info/musicItemWidthInfo.h>
#include <musicImpement/item/musicFavoriteItem.h>
#include <musicImpement/widget/musicCentreWidget.h>

#include <tools/ffmpegTools.h>

class IMusicFavoriteItem;
bool AppMusicManage::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	supperDecodeFileSuffix.clear( );
	Delete_Resource_App_Core_Ptr( musicItemWidthInfo );
	auto clearResult = unsafeClear( );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return clearResult;
}

bool AppMusicManage::unsafeClearMusicFavoriteItem( ) {
	size_t count = musicFavoriteItemVector.size( );
	if( count == 0 )
		return true;
	auto data = musicFavoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		delete data[ index ];
	musicFavoriteItemVector.clear( );
	return true;
}

bool AppMusicManage::init( ) {
	supperDecodeFileSuffix = ffmpegTools::getFFmpegSuperMusicType( );
	if( supperDecodeFileSuffix.size( ) == 0 )
		return false;
	return true;
}

bool AppMusicManage::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	return true;
}

bool AppMusicManage::initAfter( ) {
	return true;
}

bool AppMusicManage::unsafeClear( ) {
	auto clearMusicFavoriteItemResult = unsafeClearMusicFavoriteItem( );
	return clearMusicFavoriteItemResult;
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
bool AppMusicManage::addMusicItem( IMusicItem *music_item ) {
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
bool AppMusicManage::moveMusicVector( const IMusicFavoriteItem *music_favorite_item, const std::vector< IMusicItem * > &music_info_items ) {
	userMutex->lock( );
	size_t count = musicFavoriteItemVector.size( );
	auto data = musicFavoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == music_favorite_item ) {
			data[ index ]->addMusicItem( music_info_items );

			return userMutex->result_unlock( true );
		}
	userMutex->unlock( );
	return false;
}

bool AppMusicManage::clear( ) {
	userMutex->lock( );
	auto result = unsafeClear( );
	userMutex->unlock( );
	return result;
}
bool AppMusicManage::setCurrentSelectFavoriteItem( IMusicFavoriteItem *set_select_music_favorite_item ) {
	if( currenstFavoriteItem == set_select_music_favorite_item )
		return true;
	userMutex->lock( );
	auto old = currenstFavoriteItem;
	currenstFavoriteItem = nullptr;
	if( set_select_music_favorite_item == defaultFavoriteItem )
		currenstFavoriteItem = defaultFavoriteItem;
	else {
		size_t count = musicFavoriteItemVector.size( );
		if( count ) {
			auto sourceData = musicFavoriteItemVector.data( );
			size_t index = 0;
			for( ; index < count; index += 1 )
				if( sourceData[ index ] == set_select_music_favorite_item ) {
					currenstFavoriteItem = defaultFavoriteItem;
					break;
				}
		}
	}
	// 不在列表当中，重置
	if( currenstFavoriteItem == nullptr ) {
		currenstFavoriteItem = old;
		userMutex->unlock( );
		return false;
	}
	userMutex->unlock( );
	if( musicCentreWidget )
		return musicCentreWidget->repaintMusicCentreWidget( );
	return true;
}
bool AppMusicManage::getCurrentSelectFavoriteItem( IMusicFavoriteItem *&result_current_select_music_favorite_item ) const {
	result_current_select_music_favorite_item = currenstFavoriteItem;
	return true;
}
bool AppMusicManage::getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const {
	userMutex->lock( );
	bool getMusicFavoriteItem = unsafeGetMusicFavoriteItem( result_default_music_favorite_item, result_music_favorite_item );
	userMutex->unlock( );
	return getMusicFavoriteItem;
}
bool AppMusicManage::getMusicFavoriteItem( std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const {
	userMutex->lock( );
	bool getMusicFavoriteItem = unsafeGetMusicFavoriteItem( result_music_favorite_item );
	return userMutex->result_unlock( getMusicFavoriteItem );
}

IMusicItemWidthInfo * AppMusicManage::getMusicItemWidthInfo( ) const {
	return musicItemWidthInfo;
}
bool AppMusicManage::setMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) {
	if( musicItemWidthInfo->setIMusicItemWidthInfo( music_item_width_info ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicItemWidthInfo, setIMusicItemWidthInfo, tr( "配置项的宽度信息异常" ) );
	return true;
}
bool AppMusicManage::musicFileNameSupperDecoder( const QString &file_name ) const {
	size_t count = supperDecodeFileSuffix.size( );
	if( count == 0 )
		return false; // 没有正确解析后缀
	qsizetype indexOf = file_name.indexOf( "." );
	if( indexOf == -1 )
		return false; // 没有后缀
	auto compString = file_name.mid( indexOf + 1 );
	compString = compString.toUpper( );
	auto data = supperDecodeFileSuffix.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == compString )
			return true;
	return false;
}
const std::vector< QString > & AppMusicManage::getSupperDecodeFileSuffix( ) const {
	return supperDecodeFileSuffix;
}
bool AppMusicManage::unsafeGetMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const {
	result_default_music_favorite_item = defaultFavoriteItem;
	return true;
}
bool AppMusicManage::unsafeGetMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const {
	if( unsafeGetMusicFavoriteItem( result_default_music_favorite_item ) == false )
		return false;
	if( unsafeGetMusicFavoriteItem( result_music_favorite_item ) == false )
		return false;
	return true;
}
bool AppMusicManage::unsafeGetMusicFavoriteItem( std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const {
	size_t count = musicFavoriteItemVector.size( );
	if( count )
		return true;
	result_music_favorite_item.resize( count );
	auto setData = result_music_favorite_item.data( );
	auto sourceData = musicFavoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		setData[ index ] = sourceData[ index ];
	return true;
}

bool AppMusicManage::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	userMutex->lock( );
	musicCentreWidget = music_centre_widget;
	userMutex->unlock( );
	return true;
}
IMusicCentreWidget * AppMusicManage::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool AppMusicManage::getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const {
	userMutex->lock( );
	bool getMusicFavoriteItem = unsafeGetMusicFavoriteItem( result_default_music_favorite_item );
	return userMutex->result_unlock( getMusicFavoriteItem );
}
bool AppMusicManage::initDefaultMusicFavoriteItem( ) {
	userMutex->lock( );
	if( defaultFavoriteItem )
		delete defaultFavoriteItem;
	auto create = new MusicFavoriteItem;
	defaultFavoriteItem = create;
	create->setName( tr( "默认" ) );
	userMutex->unlock( );
	return true;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
