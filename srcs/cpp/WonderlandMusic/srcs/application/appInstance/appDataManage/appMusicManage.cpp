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
const IMusicItemWidthInfo & AppMusicManage::getMusicItemWidthInfo( ) const {
	return *musicItemWidthInfo;
}
bool AppMusicManage::setMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) {
	if( musicItemWidthInfo->setIMusicItemWidthInfo( music_item_width_info ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicItemWidthInfo, setIMusicItemWidthInfo, tr( "配置项的宽度信息异常" ) );
	return true;
}
bool AppMusicManage::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
MusicCentreWidget * AppMusicManage::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool AppMusicManage::getDefaultMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const {
	return false;
}
bool AppMusicManage::getIndexMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const size_t &index ) const {
	return false;
}
bool AppMusicManage::getPosYMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const size_t &pos_x ) const {
	return false;
}
bool AppMusicManage::getNameMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const QString &music_favorite_name ) const {
	return false;
}
size_t AppMusicManage::getMusicNameVector( QString &result_default_music_favorite_name, std::vector< QString > &result_music_favorite_name_vector ) const {
	return 0;
}
size_t AppMusicManage::findMusicItemAtFavoriteItem( const IMusicItem *music_item, std::vector< IMusicFavoriteItem * > &result_find_favorite_vector ) const {
	return 0;
}
size_t AppMusicManage::findNameAtMusicItem( const QString &music_name, std::vector< IMusicItem * > &result_find_music_vector ) const {
	return 0;
}
size_t AppMusicManage::findSingerAtMusicItem( const QString &music_singer, std::vector< IMusicItem * > &result_find_music_vector ) const {
	return 0;
}
size_t AppMusicManage::findFileAtMusicItem( const QString &file_path, std::vector< IMusicItem * > &result_find_music_vector ) const {
	return 0;
}
bool AppMusicManage::initDefaultMusicFavoriteItem( ) {
	return false;
}

bool AppMusicManage::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool AppMusicManage::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
