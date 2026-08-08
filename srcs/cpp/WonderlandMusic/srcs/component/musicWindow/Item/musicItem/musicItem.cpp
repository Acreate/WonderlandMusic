#include "musicItem.h"

#include <QFileInfo>
#include <QMediaPlayer>
#include <windows.h>

#include "../../musicWindow.h"

#include "../favoriteItem/favoriteItem.h"

MusicItem::MusicItem( ) : favoriteItem( nullptr ) {
}
MusicItem::MusicItem( FavoriteItem *favorite_item ) : favoriteItem( favorite_item ) {
}
MusicItem::~MusicItem( ) {
	if( favoriteItem )
		favoriteItem->removeItem( this );
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

		// todo : 项信息

		if( favoriteItem ) {
			favoriteItem->updateItem( this );
			mediaPlayer->deleteLater( );
			mediaPlayer = nullptr;
			loadedOver = true;
		} else {
			mediaPlayer->disconnect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, nullptr );
			delete mediaPlayer;
			mediaPlayer = nullptr;
			loadedOver = true;
			delete this;
		}
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
