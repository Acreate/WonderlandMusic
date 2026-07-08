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

FavoriteItem::ItemInfo::ItemInfo( const QString &name, const std::vector< MusicItem * > &music_itemv_vector, FavoriteItemWidget *favorite_item_widget ) : name( name ), musicItemvVector( music_itemv_vector ), favoriteItemWidget( favorite_item_widget ) {
	favorite_item_widget->setFavoriteName( name );
	deleteErrorObj = new QObject;
	connect( favoriteItemWidget, &QObject::destroyed, deleteErrorObj, &QObject::destroyed );
}

FavoriteItem::ItemInfo::~ItemInfo( ) {
	this->musicItemvVector.clear( );
	delete this->favoriteItemWidget;
}

FavoriteItem::FavoriteItem( const QString &name, const std::vector< MusicItem * > &music_itemv_vector ) {
	info = new ItemInfo( name, music_itemv_vector, new FavoriteItemWidget( this ) );
	info->read = false;
	info->favoriteItemWidget->setEnabled( false );
	info->favoriteItemWidget->installEventFilter( this );
	connect( info->deleteErrorObj, &QObject::destroyed, [this] ( QObject *obj ) {
		Delete_Ptr_Exception( info->deleteErrorObj, obj );
	} );

	connect( info->favoriteItemWidget, &FavoriteItemWidget::signal_change_name_finished, this, &FavoriteItem::signal_change_name_finished );
}

void FavoriteItem::setEnabled( bool enabled ) {
	info->favoriteItemWidget->setEnabled( enabled );
}

FavoriteItem::~FavoriteItem( ) {
	info->deleteErrorObj->disconnect( info->deleteErrorObj, &QObject::destroyed, this, nullptr );
	delete info;
}

bool FavoriteItem::eventFilter( QObject *watched, QEvent *event ) {
	if( watched == info->favoriteItemWidget ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::EnabledChange :
				if( info->read == false )
					event->ignore( );
				return true;
		}
	}
	return QObject::eventFilter( watched, event );
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

	QString arrayObject;
	QString arrayDataKey;
	QString arrayCountKey;
	QString itemNameKey;
	QString musicArrayKey;
	QString musicCountKey;
	if( AppJsonKeyTools::getFavoriteItem( [&] ( const FavoriteItemJsonKey &json_key ) {
		arrayObject = json_key.getFavoriteItemArrayObject( );
		arrayDataKey = json_key.getFavoriteItemArray( );
		arrayCountKey = json_key.getFavoriteItemCount( );
		itemNameKey = json_key.getFavoriteName( );

		musicArrayKey = json_key.getMusicArray( );
		musicCountKey = json_key.getMusicCount( );
	} ) == false )
		return false;

	QJsonObject converVectorObject;
	converVectorObject.insert( arrayCountKey, QString::number( count ) );
	auto conveJson = QJsonObject( );
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	auto data = conver_vector.data( );
	size_t index;
	QJsonObject itemJson;
	QJsonObject getJson;
	std::vector< size_t > resultIndex;

	for( index = 0; index < count; index += 1 ) {
		// 插入名称
		itemJson.insert( itemNameKey, data[ index ]->info->name );
		// 插入列表
		auto &musicItems = data[ index ]->info->musicItemvVector;
		appMusicManage->toMusicIndex( resultIndex, musicItems );
		size_t indexVectorCount = resultIndex.size( );
		auto indexVectorData = resultIndex.data( );
		size_t indeVecorIndex;
		for( indeVecorIndex = 0; indeVecorIndex < indexVectorCount; indeVecorIndex += 1 )
			getJson.insert( QString::number( indeVecorIndex ), QString::number( indexVectorData[ indeVecorIndex ] ) );
		itemJson.insert( musicArrayKey, getJson );
		itemJson.insert( musicCountKey, QString::number( indexVectorCount ) );
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
	QString musicArrayKey;
	QString musicCountKey;
	if( AppJsonKeyTools::getFavoriteItem( [&] ( const FavoriteItemJsonKey &json_key ) {
		arrayObject = json_key.getFavoriteItemArrayObject( );
		arrayDataKey = json_key.getFavoriteItemArray( );
		arrayCountKey = json_key.getFavoriteItemCount( );
		itemNameKey = json_key.getFavoriteName( );

		musicArrayKey = json_key.getMusicArray( );
		musicCountKey = json_key.getMusicCount( );
	} ) == false )
		return false;
	// 查找本类对象
	auto find = set_json_object.find( arrayObject );
	auto end = set_json_object.end( );
	if( find == end )
		return false;

	auto jsonObject = find.value( ).toObject( );
	end = jsonObject.end( );
	// 查找数量
	find = jsonObject.find( arrayCountKey );
	if( end == find )
		return false;
	bool conver;
	size_t count = find.value( ).toString( ).toULongLong( &conver );;
	if( conver == false )
		return false;
	if( count == 0 )
		return true;
	// 查找对象数组
	find = jsonObject.find( arrayDataKey );
	if( end == find )
		return false;
	auto object = find.value( ).toObject( );

	result_vector.resize( count );
	auto resultData = result_vector.data( );
	auto iterator = object.begin( );
	auto iterEnd = object.end( );
	size_t index;
	std::vector< size_t > resultIndex;
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	std::vector< MusicItem * > musicItems;
	for( ; iterEnd != iterator; ++iterator ) {
		auto keyString = iterator.key( );
		index = keyString.toULongLong( &conver );
		if( conver == false )
			return false;
		if( index >= count )
			return false;
		// 获取项
		jsonObject = iterator.value( ).toObject( );
		// 获取名称
		end = jsonObject.end( );
		find = jsonObject.find( itemNameKey );
		if( end == find )
			return false;
		auto favoriteName = find.value( ).toString( );
		// 获取列表
		find = jsonObject.find( musicCountKey );
		end = jsonObject.end( );
		if( find == end )
			return false;
		size_t musicIndexCount = find.value( ).toString( ).toULongLong( &conver );
		if( conver == false )
			return false;
		resultIndex.resize( musicIndexCount );
		if( musicIndexCount ) {
			find = jsonObject.find( musicArrayKey );
			end = jsonObject.end( );
			if( find == end )
				return false;

			size_t musicIndexIndex;
			size_t musicIndexVar;
			auto musicIndexData = resultIndex.data( );
			auto foreachJsonObject = find.value( ).toObject( );
			auto begin = foreachJsonObject.begin( );
			auto ref = foreachJsonObject.end( );
			for( ; begin != ref; ++begin ) {
				musicIndexIndex = begin.key( ).toULongLong( &conver );
				if( conver == false )
					return false;
				if( musicIndexIndex >= musicIndexCount )
					return false;
				musicIndexVar = begin.value( ).toString( ).toULongLong( &conver );
				if( conver == false )
					return false;
				musicIndexData[ musicIndexIndex ] = musicIndexVar;
			}
		}
		appMusicManage->fromMusicIndex( musicItems, resultIndex );
		resultData[ index ] = new FavoriteItem( favoriteName, musicItems );
	}

	return true;
}

FavoriteItem::ItemInfo * FavoriteItem::getInfo( ) const {
	return info;
}

bool FavoriteItem::getJsonData( QJsonObject &get_json_object ) const {
	return info->favoriteItemWidget->getJsonData( get_json_object );
}

bool FavoriteItem::setJsonData( const QJsonObject &set_json_object ) {
	bool jsonData = info->favoriteItemWidget->setJsonData( set_json_object );
	if( jsonData )
		emit signal_change_vector_finished( );
	return jsonData;
}

const QString & FavoriteItem::getName( ) const {
	return info->name;
}

const std::vector< MusicItem * > & FavoriteItem::getMusicItemvVector( ) const {
	return info->musicItemvVector;
}

bool FavoriteItem::appendMusicItem( MusicItem *music_item ) {
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	if( appMusicManage->getRootItem( ) == this )
		return true;
	size_t count = info->musicItemvVector.size( );
	if( count == 0 ) {
		info->musicItemvVector.emplace_back( music_item );
		return true;
	}
	auto data = info->musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ] == music_item )
			return false;
	info->musicItemvVector.emplace_back( music_item );
	emit signal_change_vector_finished( );
	return true;
}

bool FavoriteItem::appendMusicItem( const std::vector< MusicItem * > &append_item_vector ) {
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	if( appMusicManage->getRootItem( ) == this )
		return true;
	size_t count = info->musicItemvVector.size( );
	auto data = info->musicItemvVector.data( );
	size_t appCount = append_item_vector.size( );
	size_t appIndex = 0;
	size_t activeCount = 0;
	std::vector< MusicItem * > appendItem( appCount );
	auto appendBuffData = appendItem.data( );
	auto appendData = append_item_vector.data( );

	size_t index;
	for( ; appIndex < appCount; appIndex += 1 ) {
		auto compItem = appendData[ appIndex ];
		for( index = 0; index < count; index += 1 )
			if( data[ index ] == compItem )
				break;
		if( index < count )
			continue;
		appendBuffData[ activeCount ] = compItem;
		activeCount += 1;
	}
	if( activeCount == 0 )
		return false;
	if( activeCount != appCount )
		appendItem.resize( activeCount );
	info->musicItemvVector.append_range( append_item_vector );
	emit signal_change_vector_finished( );
	return true;
}

bool FavoriteItem::removeMusicItem( const MusicItem *music_item ) {
	size_t count = info->musicItemvVector.size( );
	if( count == 0 )
		return false;
	auto data = info->musicItemvVector.data( );
	std::vector< MusicItem * > buff( count );
	auto buffData = buff.data( );
	size_t buffCount = 0;
	size_t index;
	for( index = 0; index < count; index += 1 ) {
		if( data[ index ] == music_item )
			continue;
		buffData[ buffCount ] = data[ index ];
		buffCount += 1;
	}
	if( buffCount != count )
		buff.resize( buffCount );
	info->musicItemvVector = buff;
	emit signal_change_vector_finished( );
	return true;
}

bool FavoriteItem::removeMusicItem( const std::vector< MusicItem * > &remove_item_vector ) {
	size_t count = info->musicItemvVector.size( );
	if( count == 0 )
		return false;
	auto data = info->musicItemvVector.data( );
	std::vector< MusicItem * > buff( count );
	auto buffData = buff.data( );
	size_t buffCount = 0;
	size_t index;
	size_t removeCount = remove_item_vector.size( );
	auto removeData = remove_item_vector.data( );
	size_t removeIndex;
	for( index = 0; index < count; index += 1 ) {
		auto musicItem = data[ index ];
		for( removeIndex = 0; removeIndex < removeCount; removeIndex += 1 )
			if( musicItem == removeData[ removeIndex ] )
				break;
		if( removeIndex < removeCount )
			continue;
		buffData[ buffCount ] = musicItem;
		buffCount += 1;
	}
	if( buffCount != count )
		buff.resize( buffCount );
	info->musicItemvVector = buff;
	emit signal_change_vector_finished( );
	return true;
}

bool FavoriteItem::appendMusicItem( const QString &music_item ) {
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	MusicItem *getItem = nullptr;
	if( appMusicManage->findMusicItem( getItem, music_item ) == 0 )
		return false;
	return appendMusicItem( getItem );
}

bool FavoriteItem::appendMusicItem( const std::vector< QString > &append_item_vector ) {
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	if( appMusicManage->getRootItem( ) == this )
		return true;
	std::vector< MusicItem * > getItem;
	if( appMusicManage->findMusicItem( getItem, append_item_vector ) == 0 )
		return false;
	return appendMusicItem( getItem );
}

bool FavoriteItem::removeMusicItem( const QString &music_item ) {
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	MusicItem *getItem = nullptr;
	if( appMusicManage->findMusicItem( getItem, music_item ) == 0 )
		return false;
	return removeMusicItem( getItem );
}

bool FavoriteItem::removeMusicItem( const std::vector< QString > &remove_item_vector ) {
	auto appMusicManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
	std::vector< MusicItem * > getItem;
	if( appMusicManage->findMusicItem( getItem, remove_item_vector ) == 0 )
		return false;
	return removeMusicItem( getItem );
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
