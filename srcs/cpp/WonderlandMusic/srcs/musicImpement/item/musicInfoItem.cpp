#include "musicInfoItem.h"

#include <application/appInstance/appDataManage/appMusicManage.h>

#include <component/musicWindow/interface/item/iMusicFavoriteItem.h>

#include <dateTimeFormat/dateTimeFormat.h>

#include <musicImpement/itemWidget/musicItemWidget.h>

#include <musicFileInfo/musicFileInfo.h>

#include <mutex/userMutex.h>

#include <tools/pathTools.h>

MusicInfoItem::MusicInfoItem( IMusicFavoriteItem *music_favorite_item ) : musicFavoriteItem( music_favorite_item ) {
	if( music_favorite_item == nullptr ) {
		deleteLater( );
		return;
	}
	appendTypeInfo( this );
	musicItemWidget = new MusicItemWidget;
	musicItemWidget->bindMusicItem( this );
}
MusicInfoItem::MusicInfoItem( IMusicFavoriteItem *music_favorite_item, const MusicFileInfo &music_info ) : musicFavoriteItem( music_favorite_item ) {
	if( music_favorite_item == nullptr || initVar( music_info ) == false ) {
		deleteLater( );
		return;
	}
	appendTypeInfo( this );
	musicItemWidget = new MusicItemWidget;
	musicItemWidget->bindMusicItem( this );
}

MusicInfoItem::~MusicInfoItem( ) {
	if( musicFavoriteItem )
		musicFavoriteItem->removeMusicItem( this );
	if( musicItemWidget )
		delete musicItemWidget;
}
size_t MusicInfoItem::getIdCode( ) const {
	return idCode;
}
const QString & MusicInfoItem::getName( ) const {
	return name;
}
const QString & MusicInfoItem::getSinger( ) const {
	return singer;
}
const QString & MusicInfoItem::getFilePath( ) const {
	return filePath;
}
const QString & MusicInfoItem::getAbsoluteFilePath( ) const {
	return absoluteFilePath;
}

const QString & MusicInfoItem::getElapsedTimeString( ) const {
	return elapsedTimeString;
}
const qint64 & MusicInfoItem::getElapsedTime( ) const {
	return elapsedTime;
}
const QString & MusicInfoItem::getFileBaseName( ) const {
	return fileBaseName;
}
bool MusicInfoItem::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return musicItemWidget->setMusicCentreWidget( musicCentreWidget );
}
bool MusicInfoItem::setMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	musicFavoriteItem = music_favorite_item;
	return true;
}
bool MusicInfoItem::initVar( const MusicFileInfo &music_info ) {
	idCode = 0;
	name = music_info.getTitle( );
	singer = music_info.getArtist( );
	filePath = music_info.getFilePath( );
	absoluteFilePath = music_info.getAbsoluteFilePath( );
	elapsedTimeString = music_info.getDurationMillsecondDateTimeString( );
	elapsedTime = music_info.getDurationMillsecond( );
	fileBaseName = music_info.getFileBaseName( );
	return true;
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

IMusicCentreWidget * MusicInfoItem::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
IMusicItemWidget * MusicInfoItem::getMusicItemWidget( ) const {
	return musicItemWidget;
}
IMusicFavoriteItem * MusicInfoItem::getMusicFavoriteItem( ) const {
	return musicFavoriteItem;
}
