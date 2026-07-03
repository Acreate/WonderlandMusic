#include "musicItem.h"

#include <QMediaMetaData>
#include <QMediaPlayer>

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/musicInfoItemTranslate.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../tools/pathTools.h"

bool MusicItem::isMusicFile( const QString &music_file_path ) {
	return QFileInfo( music_file_path ).absoluteFilePath( ) == musicInfo.absFilePath;
}

bool MusicItem::isMusicFile( const MusicItem &music_file_path ) {
	if( this == &music_file_path || &( this->musicInfo ) == &( music_file_path.musicInfo ) )
		return true;
	return music_file_path.musicInfo.musicFilePath == this->musicInfo.musicFilePath;
}

const QString & MusicItem::getAbsFilePath( ) const {
	return musicInfo.absFilePath;
}

const QString & MusicItem::getMusicFilePath( ) const {
	return musicInfo.musicFilePath;
}

const QString & MusicItem::getMusicName( ) const {
	return musicInfo.musicName;
}

const QString & MusicItem::getMusicSinger( ) const {
	return musicInfo.musicSinger;
}

qint64 MusicItem::getDuration( ) const {
	return musicInfo.duration;
}

const QString & MusicItem::getFormatStringDuration( ) const {
	return musicInfo.formatStringDuration;
}

MusicItem::Info::~Info( ) {
}

bool MusicItem::Info::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool MusicItem::Info::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}

MusicItem::Info::Info( const QJsonObject &music_json_object ) {
	setJsonData( music_json_object );
}

MusicItem::Info::Info( const QMediaPlayer &media_player ) {
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

MusicItem::~MusicItem( ) {
}

MusicItem::MusicItem( const QMediaPlayer &media_player ) : musicInfo( media_player ) {
}

MusicItem::MusicItem( const QJsonObject &music_json_object ) : musicInfo( music_json_object ) {
}

bool MusicItem::getJsonData( QJsonObject &get_json_object ) const {
	return musicInfo.getJsonData( get_json_object );
}

bool MusicItem::setJsonData( const QJsonObject &set_json_object ) {
	return musicInfo.setJsonData( set_json_object );
}

//
//MusicItem::MusicItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration ) : musicName( music_name ), musicSinger( music_singer ), duration( duration ) {
//	musicFilePath = PathTools::getAutoShortenPathName( music_file_path );
//	absFilePath = QFileInfo( music_file_path ).absoluteFilePath( );
//	equFilePath = absFilePath == musicFilePath;
//}
