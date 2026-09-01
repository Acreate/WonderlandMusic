#include "appMusicManage.h"

#include <QPainter>

#include <component/musicWindow/interface/info/iMusicItemWidthInfo.h>
#include <component/musicWindow/interface/item/iMusicItem.h>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/init_macro.h>
#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <mutex/userMutex.h>

#include <tools/pathTools.h>

#include <musicImpement/item/musicInfoItem.h>

#include <musicImpement/info/musicItemWidthInfo.h>
#include <musicImpement/item/musicFavoriteItem.h>
#include <musicImpement/widget/musicCentreWidget.h>

#include "appMusicManage/appMusicDecoder.h"

class IMusicFavoriteItem;
bool AppMusicManage::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	if( musicCentreWidget )

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

bool AppMusicManage::init( ) {
	Init_Resource_App_Core_Ptr( appMusicDecoder );
	return true;
}

bool AppMusicManage::initBefore( ) {
	deleteResource( );
	appMusicDecoder = new AppMusicDecoder;
	userMutex = new UserMutex;
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
size_t AppMusicManage::loadMusicFile( IMusicFavoriteItem *music_favorite_item, const std::vector< QString > &music_file_path_vector ) {
	size_t result = 0;
	size_t count = music_file_path_vector.size( );
	if( count == 0 )
		return result;
	size_t index = 0;
	auto data = music_file_path_vector.data( );
	for( ; index < count; index += 1 )
		result += loadMusicFile( music_favorite_item, data[ index ] );
	return result;
}
size_t AppMusicManage::loadMusicFile( IMusicFavoriteItem *music_favorite_item, const std::list< QString > &music_file_path_list ) {
	size_t result = 0;
	auto iterator = music_file_path_list.begin( );
	auto end = music_file_path_list.end( );
	if( iterator == end )
		return result;
	for( ; iterator != end; ++iterator )
		result += loadMusicFile( music_favorite_item, *iterator );
	return result;
}
size_t AppMusicManage::loadMusicFile( IMusicFavoriteItem *music_favorite_item, const QStringList &music_file_path_list ) {
	size_t result = 0;
	size_t count = music_file_path_list.size( );
	if( count == 0 )
		return result;
	size_t index = 0;
	auto data = music_file_path_list.data( );
	for( ; index < count; index += 1 )
		result += loadMusicFile( music_favorite_item, data[ index ] );
	return result;
}
size_t AppMusicManage::loadMusicFile( IMusicFavoriteItem *music_favorite_item, const QString &music_file_path ) {
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
size_t AppMusicManage::loadMusicDir( IMusicFavoriteItem *music_favorite_item, const QString &music_dir_path ) {
	size_t result = 0;

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
				for( index = 0; index < musicFileCount; index += 1 )
					result += loadMusicFile( music_favorite_item, data[ index ] );
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
bool AppMusicManage::getMusicItemVector( std::vector< IMusicItem * > &result_music_item_vector ) const {
	userMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		result_music_item_vector.resize( count );
		auto setData = result_music_item_vector.data( );
		auto sourceData = musicItemVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			setData[ index ] = sourceData[ index ];
	}
	return userMutex->result_unlock( true );
}
IMusicItemWidthInfo * AppMusicManage::getMusicItemWidthInfo( ) const {
	return musicItemWidthInfo;
}
bool AppMusicManage::setMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) {
	if( musicItemWidthInfo->setIMusicItemWidthInfo( music_item_width_info ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicItemWidthInfo, setIMusicItemWidthInfo, tr( "配置项的宽度信息异常" ) );
	return true;
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
	defaultFavoriteItem = new MusicFavoriteItem;
	defaultFavoriteItem->setName( tr( "默认" ) );
	userMutex->unlock( );
	return true;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
