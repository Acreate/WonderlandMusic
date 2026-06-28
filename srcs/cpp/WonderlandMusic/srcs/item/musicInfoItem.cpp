#include "musicInfoItem.h"

#include <QFileInfo>
#include <QJsonObject>
#include <QMediaMetaData>

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/jsonKey/musicInfoItemJsonKey.h"
#include "../application/translate/musicInfoItemTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../tools/pathTools.h"

#include "../widget/playerListWidget.h"

MusicInfoItem::MusicInfoItem( ) : MusicInfoItem( nullptr ) {
}

MusicInfoItem::MusicInfoItem( PlayerListWidget *parent ) : parentPlayListWidget( parent ) {
}

bool MusicInfoItem::init( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration_ms ) {
	QFileInfo info( music_file_path );
	musicFilePath = PathTools::getAutoShortenPathName( music_file_path );
	absFilePath = info.absoluteFilePath( );
	musicName = music_name;
	musicSinger = music_singer;
	this->duration = duration_ms;
	this->formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration_ms );
	equFilePath = absFilePath == musicFilePath;
	return true;
}

bool MusicInfoItem::init( const QString &file_path, const QMediaMetaData &mediaMetaData ) {
	if( mediaMetaData.isEmpty( ) )
		return false;

	musicSinger = mediaMetaData.stringValue( QMediaMetaData::ContributingArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::AlbumArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::Author );
	if( musicSinger.isEmpty( ) ) {
		auto beingNameNone = AppInstance::getAppInstance( )->getAppDataManage(  )->getTranslate( )->getMusicInfoItem( )->getMusichumanBeingNameNone( );
		musicSinger = beingNameNone; // 使用匿名
	}
	duration = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
	formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration );
	musicFilePath = PathTools::getAutoShortenPathName( file_path );
	musicName = mediaMetaData.stringValue( QMediaMetaData::Title );
	if( musicName.isEmpty( ) ) {
		QFileInfo info( musicFilePath );
		musicName = info.baseName( );
	}
	QFileInfo info( file_path );
	absFilePath = info.absoluteFilePath( );
	equFilePath = absFilePath == musicFilePath;
	return true;
}

bool MusicInfoItem::isFile( const QString &comp_file ) const {
	if( equFilePath == false )
		return musicFilePath == comp_file || absFilePath == comp_file;
	return musicFilePath == comp_file;
}

const QString & MusicInfoItem::getMusicFilePath( ) const {
	return musicFilePath;
}

const QString & MusicInfoItem::getMusicName( ) const {
	return musicName;
}

const QString & MusicInfoItem::getMusicSinger( ) const {
	return musicSinger;
}

qint64 MusicInfoItem::getDuration( ) const {
	return duration;
}

const QString & MusicInfoItem::getFormatStringDuration( ) const {
	return formatStringDuration;
}

bool MusicInfoItem::renderImage( QImage &result_render_image ) const {
	if( parentPlayListWidget == nullptr )
		return false;
	return parentPlayListWidget->renderMusicInfoItem( result_render_image, this );
}

size_t MusicInfoItem::getIndex( ) const {
	return index;
}

void MusicInfoItem::setIndex( const size_t index ) {
	this->index = index;
	formatStringIndex = QString( "%1" ).arg( index, 4, 10, '0' );
}

const QString & MusicInfoItem::getFormatStringIndex( ) const {
	return formatStringIndex;
}

bool MusicInfoItem::toJsonObect( QJsonObject &result_json_object, const MusicInfoItem &music_info ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getAppDataManage(  )->getJsonFileKey( );
	auto musicInfoItemJsonKey = jsonFileKey->getMusicInfoItem( );
	result_json_object.insert( musicInfoItemJsonKey->getMusicInfoFile( ), music_info.musicFilePath );
	result_json_object.insert( musicInfoItemJsonKey->getMusicInfoName( ), music_info.musicName );
	result_json_object.insert( musicInfoItemJsonKey->getMusicInfoSinger( ), music_info.musicSinger );
	result_json_object.insert( musicInfoItemJsonKey->getMusicInfoDuration( ), music_info.duration );
	return true;
}

bool MusicInfoItem::forJsonObject( MusicInfoItem &result_music_info, const QJsonObject &for_json_object ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getAppDataManage(  )->getJsonFileKey( );

	auto musicInfoItemJsonKey = jsonFileKey->getMusicInfoItem( );
	auto end = for_json_object.end( );
	auto find = for_json_object.find( musicInfoItemJsonKey->getMusicInfoFile( ) );
	if( end == find )
		return false;
	result_music_info.musicFilePath = PathTools::getAutoShortenPathName( find.value( ).toString( ) );
	find = for_json_object.find( musicInfoItemJsonKey->getMusicInfoName( ) );
	if( end == find )
		return false;
	result_music_info.musicName = find.value( ).toString( );
	find = for_json_object.find( musicInfoItemJsonKey->getMusicInfoSinger( ) );
	if( end == find )
		return false;
	result_music_info.musicSinger = find.value( ).toString( );
	find = for_json_object.find( musicInfoItemJsonKey->getMusicInfoDuration( ) );
	if( end == find )
		return false;
	result_music_info.duration = find.value( ).toInteger( );
	result_music_info.formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( result_music_info.duration );

	QFileInfo info( result_music_info.musicFilePath );
	result_music_info.absFilePath = info.absoluteFilePath( );
	result_music_info.equFilePath = result_music_info.absFilePath == result_music_info.musicFilePath;
	return true;
}
