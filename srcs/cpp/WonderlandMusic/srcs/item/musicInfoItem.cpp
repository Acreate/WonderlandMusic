#include "musicInfoItem.h"

#include <QFileInfo>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <qimage.h>

#include "../application/appInstance/appDataManage/appMusicManage.h"

#include "../dateTimeFormat/dateTimeFormat.h"
MusicInfoItem::MusicInfoItem( AppMusicManage *app_music_manage ) : appMusicManage( app_music_manage ) {
	if( appMusicManage == nullptr ) {
		deleteLater( );
		return;
	}
	loadedOver = false;
	rendBuff = new QImage;
	appendTypeInfo( this );
}
MusicInfoItem::MusicInfoItem( AppMusicManage *app_music_manage, const QString &disk_file_path ) : appMusicManage( app_music_manage ) {
	QFileInfo fileInfo( disk_file_path );
	if( appMusicManage == nullptr || fileInfo.exists( ) == false ) {
		deleteLater( );
		return;
	}
	rendBuff = new QImage;
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
		if( removeThis ) {
			deleteLater( );
		}
		// 野指针时		
		mediaPlayer->deleteLater( );
		mediaPlayer = nullptr;
		loadedOver = true;
	} );

	auto source = QUrl::fromLocalFile( filePath );
	mediaPlayer->setSource( source );
}
MusicInfoItem::~MusicInfoItem( ) {
	if( mediaPlayer )
		delete mediaPlayer;
	if( rendBuff )
		delete rendBuff;
}
bool MusicInfoItem::isLoadedOver( ) {
	return loadedOver;
}
bool MusicInfoItem::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicInfoItem::getElapsedTimeString( QString &result_elapsed_time_string ) const {
	if( loadedOver == false )
		return false;
	result_elapsed_time_string = elapsedTimeString;
	return true;
}
bool MusicInfoItem::getIdCode( size_t &result_id_code ) const {
	if( loadedOver == false )
		return false;
	result_id_code = idCode;
	return true;
}
bool MusicInfoItem::getName( QString &result_name ) const {
	if( loadedOver == false )
		return false;
	result_name = name;
	return true;
}
bool MusicInfoItem::getSinger( QString &result_singer ) const {
	if( loadedOver == false )
		return false;
	result_singer = singer;
	return true;
}
bool MusicInfoItem::getFilePath( QString &result_file_path ) const {
	if( loadedOver == false )
		return false;
	result_file_path = absoluteFilePath;
	return true;
}
bool MusicInfoItem::getElapsedTime( size_t &result_elapsed_time ) const {
	if( loadedOver == false )
		return false;
	result_elapsed_time = elapsedTime;
	if( result_elapsed_time != elapsedTime )
		return false;
	return true;
}
bool MusicInfoItem::getDrawBuff( QImage &result_buff ) const {
	if( loadedOver == false )
		return false;
	if( rendBuff == nullptr )
		return false;
	result_buff = *rendBuff;
	return true;
}
bool MusicInfoItem::setDrawBuff( QImage &image ) {
	if( loadedOver == false )
		return false;
	if( rendBuff == nullptr )
		return false;
	*rendBuff = image;
	return true;
}
