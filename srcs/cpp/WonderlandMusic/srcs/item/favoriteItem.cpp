#include "favoriteItem.h"
#include <QJsonObject>
#include "musicItem.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appMusicManage.h"
#include "../application/jsonKey/favoriteItemJsonKey.h"
#include "../application/translate/deleteExceptionTranslate.h"
#include "../itemWidget/favoriteItemWidget.h"
#include "../msgInfo/deleteException.h"
#include "../msgInfo/messageErrorOut.h"
#include "../tools/appJsonKeyTools.h"
#include "../tools/appTranslateTools.h"
#include "../tools/jsonObjectTools.h"

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

bool FavoriteItem::getJsonDataVector( QJsonObject &get_json_object, const std::vector< FavoriteItem * > &conver_vector ) {
	size_t count = conver_vector.size( );
	if( count == 0 )
		return false;
	QString arrayObject;
	QString arrayDataKey;
	QString arrayCountKey;
	QString itemNameKey;
	if( AppJsonKeyTools::getFavoriteItem( [&] ( const FavoriteItemJsonKey &json_key ) {
		arrayObject = json_key.getFavoriteItemArrayObject( );
		arrayDataKey = json_key.getFavoriteItemArray( );
		arrayCountKey = json_key.getFavoriteItemCount( );
		itemNameKey = json_key.getFavoriteName( );
	} ) == false )
		return false;

	QJsonObject conveJson;
	if( JsonObjectTools::toJson( conveJson, count ) == false )
		return false;
	QJsonObject converVectorObject;
	converVectorObject.insert( arrayCountKey, conveJson );
	conveJson = QJsonObject( );
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	auto data = conver_vector.data( );
	size_t index;
	QJsonObject itemJson;
	QJsonObject getJson;
	std::vector< size_t > resultIndex;
	for( index = 0; index < count; index += 1 ) {
		// 插入名称
		if( JsonObjectTools::toJson( getJson, data[ index ]->info->name ) == false )
			return false;
		itemJson.insert( itemNameKey, getJson );
		// 插入列表
		auto &musicItems = data[ index ]->info->musicItemvVector;
		getJson = QJsonObject( );
		appMusicManage->toMusicIndex( resultIndex, musicItems );
		if( JsonObjectTools::toJson( getJson, resultIndex ) == false )
			return false;
		itemJson.insert( itemNameKey, getJson );
		// 插入到项
		conveJson.insert( QString::number( index ), itemJson );
		itemJson = QJsonObject( );
		getJson = QJsonObject( );
	}
	converVectorObject.insert( arrayDataKey, conveJson );
	get_json_object.insert( arrayObject, converVectorObject );
	return true;
}

bool FavoriteItem::setJsonDataVector( std::vector< FavoriteItem * > &result_vector, const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;

	QString arrayObject;
	QString arrayDataKey;
	QString arrayCountKey;
	QString itemNameKey;
	if( AppJsonKeyTools::getFavoriteItem( [&] ( const FavoriteItemJsonKey &json_key ) {
		arrayObject = json_key.getFavoriteItemArrayObject( );
		arrayDataKey = json_key.getFavoriteItemArray( );
		arrayCountKey = json_key.getFavoriteItemCount( );
		itemNameKey = json_key.getFavoriteName( );
	} ) == false )
		return false;

	auto find = set_json_object.find( arrayObject );
	auto end = set_json_object.end( );
	if( find == end )
		return false;
	auto jsonObject = find.value( ).toObject( );
	end = jsonObject.end( );
	find = jsonObject.find( arrayCountKey );
	if( end == find )
		return false;
	auto object = find.value( ).toObject( );
	size_t count;
	if( JsonObjectTools::toObject( count, object ) == false )
		return false;

	if( count == 0 )
		return true;
	find = jsonObject.find( arrayDataKey );
	if( end == find )
		return false;
	object = find.value( ).toObject( );
	result_vector.resize( count );
	auto resultData = result_vector.data( );
	auto iterator = object.begin( );
	auto iterEnd = object.end( );
	bool conver;
	size_t index;
	std::vector< size_t > resultIndex;
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	std::vector< MusicItem * > musicItems;
	for( ; iterEnd != iterator; ++iterator ) {
		auto keyString = iterEnd.key( );
		index = keyString.toULongLong( &conver );
		if( conver == false )
			return false;
		if( index <= count )
			return false;
		// 获取项
		jsonObject = iterEnd.value( ).toObject( );
		// 获取名称
		end = jsonObject.end( );
		find = jsonObject.find( itemNameKey );
		if( end == find )
			return false;
		auto favoriteName = find.value( ).toString( );
		// 获取列表
		find = jsonObject.find( itemNameKey );
		if( end == find )
			return false;
		auto jsonValueRefs = find.value( ).toObject( );
		if( JsonObjectTools::toObject( resultIndex, jsonValueRefs ) == false )
			return false;
		appMusicManage->fromMusicIndex( musicItems, resultIndex );
		resultData[ index ] = new FavoriteItem( favoriteName, musicItems );
	}

	return true;
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
