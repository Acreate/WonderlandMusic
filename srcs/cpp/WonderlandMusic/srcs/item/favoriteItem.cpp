#include "favoriteItem.h"
#include "musicItem.h"
#include "../application/translate/deleteExceptionTranslate.h"
#include "../itemWidget/favoriteItemWidget.h"
#include "../msgInfo/deleteException.h"
#include "../msgInfo/messageErrorOut.h"
#include "../tools/appTranslateTools.h"

FavoriteItem::ItemInfo::ItemInfo( const QString &name, const std::vector< MusicItem * > &music_itemv_vector, FavoriteItemWidget *favorite_item_widget ) : name( name ), musicItemvVector( music_itemv_vector ),
	favoriteItemWidget( favorite_item_widget ) {
	deleteErrorObj = new QObject;
	connect( favoriteItemWidget, &QObject::destroyed, deleteErrorObj, &QObject::destroyed );
}

FavoriteItem::ItemInfo::~ItemInfo( ) {
	this->musicItemvVector.clear( );
	delete this->favoriteItemWidget;
}

FavoriteItem::FavoriteItem( const QString &name, const std::vector< MusicItem * > &music_itemv_vector ) {
	info = new ItemInfo( name, music_itemv_vector, new FavoriteItemWidget( this ) );
	connect( info->deleteErrorObj, &QObject::destroyed, [this] ( QObject *obj ) {
		Delete_Ptr_Exception( info->deleteErrorObj, obj );
	} );

	connect( info->favoriteItemWidget, &FavoriteItemWidget::signal_change_name_finished, this, &FavoriteItem::signal_change_name_finished );
}

void FavoriteItem::setEnabled( bool enabled ) {
	info->favoriteItemWidget->setEnabled( enabled );
}

FavoriteItem::FavoriteItem( const QString &name ) : FavoriteItem( name, std::vector< MusicItem * >( ) ) {
}

FavoriteItem::~FavoriteItem( ) {
	info->deleteErrorObj->disconnect( );
	delete info;
}

void FavoriteItem::setFavoriteName( const QString &favorite_name ) {
	info->favoriteItemWidget->setFavoriteName( favorite_name );
}

QString FavoriteItem::getFavoriteName( ) const {
	return info->favoriteItemWidget->getFavoriteName( );
}

FavoriteItemWidget * FavoriteItem::getFavoriteItemWidget( ) const {
	return info->favoriteItemWidget;
}

bool FavoriteItem::getJsonData( QJsonObject &get_json_object ) const {
	return info->favoriteItemWidget->getJsonData( get_json_object );
}

bool FavoriteItem::setJsonData( const QJsonObject &set_json_object ) {
	return info->favoriteItemWidget->setJsonData( set_json_object );
}

const QString & FavoriteItem::getName( ) const {
	return info->name;
}

const std::vector< MusicItem * > & FavoriteItem::getMusicItemvVector( ) const {
	return info->musicItemvVector;
}

bool FavoriteItem::appendMusicItem( MusicItem *music_item ) {
	size_t count = info->musicItemvVector.size( );
	if( count == 0 ) {
		info->musicItemvVector.emplace_back( music_item );
		return true;
	}
	auto data = info->musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ] == music_item || data[ index ]->isMusicFile( *music_item ) )
			return false;
	info->musicItemvVector.emplace_back( music_item );
	return true;
}

std::vector< MusicItem * > FavoriteItem::findMusicName( const QString &find_name ) const {
	std::vector< MusicItem * > result;
	size_t count = info->musicItemvVector.size( );
	if( count == 0 )
		return result;
	auto data = info->musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->getMusicName( ) == find_name )
			result.emplace_back( data[ index ] );
	return result;
}

std::vector< MusicItem * > FavoriteItem::findMusicFilePath( const QString &find_file_path ) const {
	std::vector< MusicItem * > result;
	size_t count = info->musicItemvVector.size( );
	if( count == 0 )
		return result;
	auto data = info->musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->isMusicFile( find_file_path ) )
			result.emplace_back( data[ index ] );
	return result;
}

std::vector< MusicItem * > FavoriteItem::findMusicMusicSinger( const QString &music_singer ) const {
	std::vector< MusicItem * > result;
	size_t count = info->musicItemvVector.size( );
	if( count == 0 )
		return result;
	auto data = info->musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->getMusicSinger( ) == music_singer )
			result.emplace_back( data[ index ] );
	return result;
}
