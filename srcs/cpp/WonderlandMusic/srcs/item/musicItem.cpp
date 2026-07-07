#include "musicItem.h"
#include <QJsonObject>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <windows.h>
#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonKey/musicItemJsonKey.h"
#include "../application/translate/deleteExceptionTranslate.h"
#include "../application/translate/musicInfoItemTranslate.h"
#include "../dateTimeFormat/dateTimeFormat.h"
#include "../itemWidget/musicInfoItemWidget.h"
#include "../msgInfo/deleteException.h"
#include "../tools/appJsonKeyTools.h"
#include "../tools/appTranslateTools.h"
#include "../tools/arrayTools.h"
#include "../tools/pathTools.h"

bool MusicItem::isMusicFile( const QString &music_file_path ) {
	return QFileInfo( music_file_path ).absoluteFilePath( ) == musicInfo->absFilePath;
}

bool MusicItem::isMusicFile( const MusicItem &music_file_path ) {
	if( this == &music_file_path || &( this->musicInfo ) == &( music_file_path.musicInfo ) )
		return true;
	return music_file_path.musicInfo->musicFilePath == this->musicInfo->musicFilePath;
}

const QString & MusicItem::getAbsFilePath( ) const {
	return musicInfo->absFilePath;
}

const QString & MusicItem::getMusicFilePath( ) const {
	return musicInfo->musicFilePath;
}

const QString & MusicItem::getMusicName( ) const {
	return musicInfo->musicName;
}

const QString & MusicItem::getMusicSinger( ) const {
	return musicInfo->musicSinger;
}

qint64 MusicItem::getDuration( ) const {
	return musicInfo->duration;
}

const QString & MusicItem::getFormatStringDuration( ) const {
	return musicInfo->formatStringDuration;
}

MusicInfoItemWidget * MusicItem::getMusicInfoItemWidget( ) const {
	return musicInfo->musicInfoItemWidget;
}

MusicItem::Info::~Info( ) {
	delete musicInfoItemWidget;
}

bool MusicItem::Info::getJsonData( QJsonObject &get_json_object ) const {
	return musicInfoItemWidget->getJsonData( get_json_object );
}

bool MusicItem::Info::setJsonData( const QJsonObject &set_json_object ) {
	return musicInfoItemWidget->setJsonData( set_json_object );
}

MusicItem::Info::Info( const QJsonObject &music_json_object, MusicItem *music_item ) {
	musicInfoItemWidget = new MusicInfoItemWidget( *music_item );
	deleteErrorObj = new QObject;
	connect( musicInfoItemWidget, &QObject::destroyed, deleteErrorObj, &QObject::destroyed );
	setJsonData( music_json_object );
}

MusicItem::Info::Info( const QMediaPlayer &media_player, MusicItem *music_item ) {
	musicInfoItemWidget = new MusicInfoItemWidget( *music_item );
	deleteErrorObj = new QObject;
	connect( musicInfoItemWidget, &QObject::destroyed, deleteErrorObj, &QObject::destroyed );
	auto localFile = media_player.source( ).toLocalFile( );
	auto &&mediaMetaData = media_player.metaData( );
	musicSinger = mediaMetaData.stringValue( QMediaMetaData::ContributingArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::AlbumArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::Author );
	if( musicSinger.isEmpty( ) ) {
		auto beingNameNone = AppInstance::getAppInstance( )->getAppDataManage( )->getTranslate( )->getMusicInfoItem( )->getMusichumanBeingNameNone( );
		musicSinger = beingNameNone; // 使用匿名
	}
	duration = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
	formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration );
	musicFilePath = PathTools::getAutoShortenPathName( localFile );
	musicName = mediaMetaData.stringValue( QMediaMetaData::Title );
	if( musicName.isEmpty( ) ) {
		QFileInfo info( musicFilePath );
		musicName = info.baseName( );
	}
	QFileInfo info( localFile );
	absFilePath = info.absoluteFilePath( );
	equFilePath = absFilePath == musicFilePath;
}

bool MusicItem::Info::isEquFilePath( ) const {
	return equFilePath;
}

const QString & MusicItem::Info::getAbsFilePath( ) const {
	return absFilePath;
}

const QString & MusicItem::Info::getMusicFilePath( ) const {
	return musicFilePath;
}

const QString & MusicItem::Info::getMusicName( ) const {
	return musicName;
}

const QString & MusicItem::Info::getMusicSinger( ) const {
	return musicSinger;
}

qint64 MusicItem::Info::getDuration( ) const {
	return duration;
}

const QString & MusicItem::Info::getFormatStringDuration( ) const {
	return formatStringDuration;
}

MusicInfoItemWidget * MusicItem::Info::getMusicInfoItemWidget( ) const {
	return musicInfoItemWidget;
}

MusicItem * MusicItem::Info::getMusicItem( ) const {
	return musicItem;
}

MusicItem::~MusicItem( ) {
	musicInfo->deleteErrorObj->disconnect( );
	disconnect( );
	delete musicInfo;
}

MusicItem::MusicItem( const QMediaPlayer &media_player ) {
	musicInfo = new Info( media_player, this );
	connect( musicInfo->deleteErrorObj, &QObject::destroyed, [this] ( QObject *delete_obj_ptr ) {
		Delete_Ptr_Exception( musicInfo->deleteErrorObj, delete_obj_ptr );
	} );
}

MusicItem::MusicItem( const QJsonObject &music_json_object ) {
	musicInfo = new Info( music_json_object, this );
	connect( musicInfo->deleteErrorObj, &QObject::destroyed, [this] ( QObject *delete_obj_ptr ) {
		Delete_Ptr_Exception( musicInfo->deleteErrorObj, delete_obj_ptr );
	} );
}

bool MusicItem::getJsonDataVector( QJsonObject &get_json_object, const std::vector< MusicItem * > &conver_vector ) {
	QString musicVectorJsonKey;
	QString musicCountJsonKey;
	QString musicDataJsonKey;

	if( AppJsonKeyTools::getMusicItem( [&] ( const MusicItemJsonKey &json_key ) {
		musicVectorJsonKey = json_key.getMusicVector( );
		musicCountJsonKey = json_key.getMusicCount( );
		musicDataJsonKey = json_key.getMusicData( );
	} ) == false )
		return false;

	QJsonObject vectorData;
	size_t count = conver_vector.size( );
	auto data = conver_vector.data( );
	size_t index = 0;
	size_t jsonCount = 0;
	for( ; index < count; index += 1 ) {
		QJsonObject getJson;
		if( data[ index ]->getJsonData( getJson ) ) {
			vectorData.insert( QString::number( jsonCount ), getJson );
			jsonCount += 1;
		}
	}
	QJsonObject vector;
	vector.insert( musicDataJsonKey, vectorData );
	vector.insert( musicCountJsonKey, QString::number( jsonCount ) );
	get_json_object.insert( musicVectorJsonKey, vector );
	return true;
}

bool MusicItem::setJsonDataVector( std::vector< MusicItem * > &result_vector, const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;

	QString musicVectorJsonKey;
	QString musicCountJsonKey;
	QString musicDataJsonKey;

	if( AppJsonKeyTools::getMusicItem( [&] ( const MusicItemJsonKey &json_key ) {
		musicVectorJsonKey = json_key.getMusicVector( );
		musicCountJsonKey = json_key.getMusicCount( );
		musicDataJsonKey = json_key.getMusicData( );
	} ) == false )
		return false;

	auto find = set_json_object.find( musicVectorJsonKey );
	auto end = set_json_object.end( );
	if( find == end )
		return false;
	QJsonObject vector = find.value( ).toObject( );
	end = vector.end( );

	find = vector.find( musicCountJsonKey );
	if( find == end )
		return false;
	bool conver;
	auto vectorCount = find->toString( ).toULongLong( &conver );
	if( conver == false )
		return false;
	if( vectorCount == 0 )
		return true;
	find = vector.find( musicDataJsonKey );
	if( find == end )
		return false;
	result_vector.resize( vectorCount );
	auto setData = result_vector.data( );
	QJsonObject vectorData = find.value( ).toObject( );
	auto begin = vectorData.begin( );
	end = vectorData.end( );
	for( ; begin != end; ++begin ) {
		auto index = begin.key( ).toULongLong( &conver );
		if( conver == false )
			continue;
		if( index >= vectorCount )
			continue;
		auto jsonObject = begin.value( ).toObject( );
		auto musicItem = new MusicItem( jsonObject );
		setData[ index ] = musicItem;
	}
	vectorCount = ArrayTools::sortNullptr( setData, vectorCount );
	result_vector.resize( vectorCount );
	return true;
}

bool MusicItem::getJsonData( QJsonObject &get_json_object ) const {
	return musicInfo->getJsonData( get_json_object );
}

bool MusicItem::setJsonData( const QJsonObject &set_json_object ) {
	return musicInfo->setJsonData( set_json_object );
}
