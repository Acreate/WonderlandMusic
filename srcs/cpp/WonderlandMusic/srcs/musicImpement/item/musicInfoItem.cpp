#include "musicInfoItem.h"

#include <QMediaPlayer>
#include <qimage.h>

#include <mutex/userMutex.h>

#include <musicImpement/itemWidget/musicItemWidget.h>

#include <application/appInstance/appDataManage/appMusicManage.h>

#include <dateTimeFormat/dateTimeFormat.h>

#include <tools/pathTools.h>

#include "../../msgInfo/outDebug.h"

#include "../../musicPlayer/musicInfo.h"

MusicInfoItem::MusicInfoItem( AppMusicManage *app_music_manage ) : appMusicManage( app_music_manage ) {
	musicItemWidget = new MusicItemWidget;
	binMusicItemWidget( musicItemWidget, this );
	if( appMusicManage == nullptr ) {
		deleteLater( );
		return;
	}
	appendTypeInfo( this );
}
MusicInfoItem::MusicInfoItem( AppMusicManage *app_music_manage, IMusicFavoriteItem *music_favorite_item, const MusicInfo &music_info ) {
	musicItemWidget = new MusicItemWidget;
	binMusicItemWidget( musicItemWidget, this );
	if( appMusicManage == nullptr || initVar( music_info ) == false ) {
		deleteLater( );
		return;
	}
	appendTypeInfo( this );
}

MusicInfoItem::~MusicInfoItem( ) {
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
bool MusicInfoItem::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicInfoItem::initVar( const MusicInfo &music_info ) {
	idCode = 0;
	singer = music_info.getArtist( );
	filePath = music_info.getFilePath( );
	absoluteFilePath = music_info.getAbsoluteFilePath( );
	elapsedTimeString = music_info.getDurationMillsecondDateTimeString( );
	elapsedTime = music_info.getDurationMillsecond( );
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
