#include "musicInfoItemWidget.h"

#include <QJsonObject>
#include <QMediaMetaData>

#include "../application/appInstance.h"
#include "../application/jsonFileKey.h"

#include "../tools/dateTimeFormat.h"

bool MusicInfoItemWidget::init( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration_ms ) {
	musicFilePath = music_file_path;
	musicName = music_name;
	musicSinger = music_singer;
	this->duration = duration_ms;
	this->formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration_ms );
	return true;
}
bool MusicInfoItemWidget::init( const QString &file_path, const QMediaMetaData &mediaMetaData ) {
	if( mediaMetaData.isEmpty( ) )
		return false;
	musicName = mediaMetaData.stringValue( QMediaMetaData::Title );
	musicSinger = mediaMetaData.stringValue( QMediaMetaData::ContributingArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::AlbumArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::Author );
	duration = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
	formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration );
	return true;
}
bool MusicInfoItemWidget::toJsonObect( QJsonObject &result_json_object, const MusicInfoItemWidget &music_info ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	result_json_object.insert( jsonFileKey->getMusicInfoFile( ), music_info.musicFilePath );
	result_json_object.insert( jsonFileKey->getMusicInfoName( ), music_info.musicName );
	result_json_object.insert( jsonFileKey->getMusicInfoSinger( ), music_info.musicSinger );
	result_json_object.insert( jsonFileKey->getMusicInfoDuration( ), music_info.duration );
	return true;
}
bool MusicInfoItemWidget::forJsonObject( MusicInfoItemWidget &result_music_info, const QJsonObject &for_json_object ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );

	auto end = for_json_object.end( );
	auto find = for_json_object.find( jsonFileKey->getMusicInfoFile( ) );
	if( end == find )
		return false;
	result_music_info.musicFilePath = find.value( ).toString( );
	find = for_json_object.find( jsonFileKey->getMusicInfoName( ) );
	if( end == find )
		return false;
	result_music_info.musicName = find.value( ).toString( );
	find = for_json_object.find( jsonFileKey->getMusicInfoSinger( ) );
	if( end == find )
		return false;
	result_music_info.musicSinger = find.value( ).toString( );
	find = for_json_object.find( jsonFileKey->getMusicInfoDuration( ) );
	if( end == find )
		return false;
	result_music_info.duration = find.value( ).toInteger( );
	result_music_info.formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( result_music_info.duration );
	return true;
}
