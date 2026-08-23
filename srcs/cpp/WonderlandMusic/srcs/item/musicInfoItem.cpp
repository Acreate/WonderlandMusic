#include "musicInfoItem.h"

#include <QFileInfo>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <qimage.h>

#include "../application/appInstance/appDataManage/appMusicManage.h"

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../mutex/userMutex.h"

#include "../tools/pathTools.h"
MusicInfoItem::MusicInfoItem( AppMusicManage *app_music_manage ) : appMusicManage( app_music_manage ) {
	userMutex = new UserMutex;
	if( appMusicManage == nullptr ) {
		deleteLater( );
		return;
	}
	loadedOver = false;
	appendTypeInfo( this );
}
MusicInfoItem::MusicInfoItem( AppMusicManage *app_music_manage, const QString &disk_file_path ) : appMusicManage( app_music_manage ) {
	userMutex = new UserMutex;
	QFileInfo fileInfo( disk_file_path );
	if( appMusicManage == nullptr || fileInfo.exists( ) == false ) {
		deleteLater( );
		return;
	}
	appendTypeInfo( this );
	filePath = fileInfo.absoluteFilePath( );
	mediaPlayer = new QMediaPlayer( );

	connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [this] ( QMediaPlayer::MediaStatus status ) {
		switch( status ) {
			case QMediaPlayer::LoadedMedia :
				break;
			default :
				return;
		}

		disconnect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, nullptr );
		userMutex->lock( );
		bool removeThis = true;
		if( appMusicManage ) {
			auto localFile = mediaPlayer->source( ).toLocalFile( );
			QFileInfo info( localFile );
			absoluteFilePath = info.absoluteFilePath( );
			filePath = info.fileName( );
			auto &&mediaMetaData = mediaPlayer->metaData( );
			this->singer = mediaMetaData.stringValue( QMediaMetaData::ContributingArtist );
			if( singer.isEmpty( ) )
				singer = mediaMetaData.stringValue( QMediaMetaData::AlbumArtist );
			if( singer.isEmpty( ) )
				singer = mediaMetaData.stringValue( QMediaMetaData::Author );
			if( singer.isEmpty( ) )
				singer = tr( "匿名" ); // 使用匿名
			elapsedTime = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
			elapsedTimeString = DateTimeFormat::millsecondToHourMinSecFrom( elapsedTime );
			name = mediaMetaData.stringValue( QMediaMetaData::Title );
			if( name.isEmpty( ) )
				name = info.baseName( );
			if( appMusicManage->hasMusicFile( absoluteFilePath ) == false )
				appMusicManage->addMusicItem( this );
			else
				appMusicManage->updateMusicItem( this );
			removeThis = false;
		}
		// 野指针时		
		mediaPlayer->deleteLater( );
		mediaPlayer = nullptr;
		loadedOver = true;
		userMutex->unlock( );
		if( removeThis )
			deleteLater( );
	} );

	auto source = QUrl::fromLocalFile( filePath );
	mediaPlayer->setSource( source );
}
MusicInfoItem::~MusicInfoItem( ) {
	userMutex->lock( );
	if( mediaPlayer )
		delete mediaPlayer;
	mediaPlayer = nullptr;
	userMutex->unlock( );
	delete userMutex;
	userMutex = nullptr;
}
bool MusicInfoItem::isLoadedOver( ) {
	userMutex->lock( );
	return userMutex->result_unlock( loadedOver );
}
bool MusicInfoItem::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	userMutex->lock( );
	musicCentreWidget = music_centre_widget;
	return userMutex->result_unlock( true );
}
bool MusicInfoItem::getElapsedTimeString( QString &result_elapsed_time_string ) const {
	userMutex->lock( );
	if( loadedOver == false )
		return userMutex->result_unlock( false );
	result_elapsed_time_string = elapsedTimeString;
	return userMutex->result_unlock( true );
}
bool MusicInfoItem::getIdCode( size_t &result_id_code ) const {
	userMutex->lock( );
	if( loadedOver == false )
		return userMutex->result_unlock( false );
	result_id_code = idCode;
	return userMutex->result_unlock( true );
}
bool MusicInfoItem::getName( QString &result_name ) const {
	userMutex->lock( );
	if( loadedOver == false )
		return userMutex->result_unlock( false );
	result_name = name;
	return userMutex->result_unlock( true );
}
bool MusicInfoItem::getSinger( QString &result_singer ) const {
	userMutex->lock( );
	if( loadedOver == false )
		return userMutex->result_unlock( false );
	result_singer = singer;
	return userMutex->result_unlock( true );
}
bool MusicInfoItem::getFilePath( QString &result_file_path ) const {
	userMutex->lock( );
	if( loadedOver == false )
		return userMutex->result_unlock( false );
	result_file_path = absoluteFilePath;
	return userMutex->result_unlock( true );
}
bool MusicInfoItem::getElapsedTime( size_t &result_elapsed_time ) const {
	userMutex->lock( );
	if( loadedOver == false )
		return userMutex->result_unlock( false );
	result_elapsed_time = elapsedTime;
	if( result_elapsed_time != elapsedTime )
		return userMutex->result_unlock( false );
	return userMutex->result_unlock( true );
}
void MusicInfoItem::setIdCode( const size_t id_code ) {
	idCode = id_code;
}
void MusicInfoItem::setName( const QString &name ) {
	this->name = name;
}
void MusicInfoItem::setSinger( const QString &singer ) {
	this->singer = singer;
}
void MusicInfoItem::setAbsoluteFilePath( const QString &absolute_file_path ) {
	QFileInfo info( absolute_file_path );
	absoluteFilePath = info.absoluteFilePath( );
	filePath = PathTools::getAutoShortenPathName( absolute_file_path );
}
void MusicInfoItem::setElapsedTime( const qint64 elapsed_time ) {
	elapsedTime = elapsed_time;
	elapsedTimeString = DateTimeFormat::millsecondToHourMinSecFrom( elapsed_time );
}
void MusicInfoItem::setLoadedOver( const bool loaded_over ) {
	loadedOver = loaded_over;
}
MusicCentreWidget * MusicInfoItem::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
