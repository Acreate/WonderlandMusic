#include "musicItem.h"

#include <QFileInfo>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <windows.h>

#include "../../musicWindow.h"

#include "../../../../dateTimeFormat/dateTimeFormat.h"

#include "../../../../tools/pathTools.h"

#include "../../musicLoad/musicLoad.h"

#include "../../tools/musicLoadTools.h"

#include "../favoriteItem/favoriteItem.h"

MusicItem::MusicItem( ) : favoriteItem( nullptr ) {
}
MusicItem::MusicItem( FavoriteItem *favorite_item ) : favoriteItem( favorite_item ) {
}
MusicItem::~MusicItem( ) {
	if( loadPtr )
		MusicLoadTools::removeMusicItemsHistory( loadPtr, this );
	if( favoriteItem )
		favoriteItem->removeMusicItem( this );
	if( mediaPlayer ) {
		delete mediaPlayer;
		mediaPlayer = nullptr;
	}
	if( rendBuff ) {
		delete rendBuff;
		rendBuff = nullptr;
	}
}
MusicItem::MusicItem( FavoriteItem *favorite_item, const QString &file_path ) : loadedOver( false ), favoriteItem( favorite_item ) {
	QFileInfo fileInfo( file_path );
	if( fileInfo.exists( ) == false ) {
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
		if( favoriteItem ) {
			auto localFile = mediaPlayer->source( ).toLocalFile( );
			QFileInfo info( localFile );
			absoluteFilePath = info.absoluteFilePath( );
			if( favoriteItem->hasMusicFile( absoluteFilePath ) == false ) {
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
				favoriteItem->updateMusicItem( this );
				MusicLoadTools::removeMusicItemsHistory( loadPtr, this );
				loadPtr = nullptr;
				removeThis = false;
			}
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
bool MusicItem::isLoadedOver( ) {
	return loadedOver;
}
bool MusicItem::getIdCode( quint64 &result_id_code ) const {
	if( loadedOver == false )
		return loadedOver;
	result_id_code = idCode;
	return loadedOver;
}
bool MusicItem::getName( QString &result_name ) const {
	if( loadedOver == false )
		return loadedOver;
	result_name = this->name;
	return loadedOver;
}
bool MusicItem::getSinger( QString &result_singer ) const {
	if( loadedOver == false )
		return loadedOver;
	result_singer = this->singer;
	return loadedOver;
}
bool MusicItem::getFilePath( QString &result_file_path ) const {
	if( loadedOver == false )
		return loadedOver;
	result_file_path = this->filePath;
	return loadedOver;
}
bool MusicItem::getElapsedTime( qint64 &result_elapsed_time ) const {
	if( loadedOver == false )
		return loadedOver;
	result_elapsed_time = this->elapsedTime;
	return loadedOver;
}
QImage * MusicItem::getRendBuff( ) const {
	return rendBuff;
}
bool MusicItem::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicItem::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
