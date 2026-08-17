#include "musicInfoItem.h"

#include <QFileInfo>
#include <QMediaMetaData>
#include <QMediaPlayer>

#include "../application/appInstance/appDataManage/appMusicManage.h"

#include "../dateTimeFormat/dateTimeFormat.h"
MusicInfoItem::MusicInfoItem( AppMusicManage *app_music_manage ) : appMusicManage( app_music_manage ) {
	if( appMusicManage == nullptr ) {
		deleteLater( );
		return;
	}
}
MusicInfoItem::MusicInfoItem( AppMusicManage *app_music_manage, const QString &disk_file_path ) : appMusicManage( app_music_manage ) {
	QFileInfo fileInfo( disk_file_path );
	if( appMusicManage == nullptr || fileInfo.exists( ) == false ) {
		deleteLater( );
		return;
	}
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
			MusicLoadTools::removeMusicItemsHistory( loadPtr, this );
			loadPtr = nullptr;
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
bool MusicInfoItem::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	return false;
}
bool MusicInfoItem::getElapsedTimeString( QString &result_elapsed_time_string ) const {
	return false;
}
QImage * MusicInfoItem::createResizeBuff( const int &width, const int &height ) {
	return nullptr;
}
MusicInfoItem::~MusicInfoItem( ) {
}
bool MusicInfoItem::isLoadedOver( ) {
	return false;
}
bool MusicInfoItem::getIdCode( size_t &result_id_code ) const {
	return false;
}
bool MusicInfoItem::getName( QString &result_name ) const {
	return false;
}
bool MusicInfoItem::getSinger( QString &result_singer ) const {
	return false;
}
bool MusicInfoItem::getFilePath( QString &result_file_path ) const {
	return false;
}
bool MusicInfoItem::getElapsedTime( size_t &result_elapsed_time ) const {
	return false;
}
bool MusicInfoItem::getRendBuff( QImage &result_buff ) const {
	return false;
}
