#include "musicItem.h"

#include <QJsonObject>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <windows.h>

#include <application/appInstance/appDataManage/jsonKey/musicItemJsonKey.h>

#include <dateTimeFormat/dateTimeFormat.h>

#include <head/result_message_out.h>

#include <tools/pathTools.h>

#include "../../musicWindow.h"

#include "../../musicLoad/musicLoad.h"

#include "../../tools/musicLoadTools.h"

#include "../favoriteItem/favoriteItem.h"

MusicItem::MusicItem( ) {
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
			if( favoriteItem->hasMusicFile( absoluteFilePath ) == false )
				favoriteItem->addMusicItem( this );
			else
				favoriteItem->updateMusicItem( this );
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
	if( AppJsonKeyTools::getMusicItem( [&get_json_object, this] ( const MusicItemJsonKey &json_key ) {
		auto &filePathKey = json_key.getAbsoluteFilePathKey( );
		auto &timeKey = json_key.getElapsedTimeKey( );
		auto &idCodeKey = json_key.getIdCodeKey( );
		auto &nameKey = json_key.getNameKey( );
		auto &singerKey = json_key.getSingerKey( );

		get_json_object.insert( filePathKey, absoluteFilePath );
		get_json_object.insert( timeKey, QString::number( elapsedTime ) );
		get_json_object.insert( idCodeKey, QString::number( idCode ) );
		get_json_object.insert( nameKey, name );
		get_json_object.insert( singerKey, singer );
		return true;
	} ) == false )
		return false;
	return true;
}
bool MusicItem::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getMusicItem( [&set_json_object,this] ( const MusicItemJsonKey &json_key ) {
		auto &filePathKey = json_key.getAbsoluteFilePathKey( );
		auto &timeKey = json_key.getElapsedTimeKey( );
		auto &idCodeKey = json_key.getIdCodeKey( );
		auto &nameKey = json_key.getNameKey( );
		auto &singerKey = json_key.getSingerKey( );

		auto end = set_json_object.end( );

		auto find = set_json_object.find( filePathKey );
		if( find == end )
			return Result_Var_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 数据失败: %1" ).arg( filePathKey ) );
		auto findFileAbsPath = find.value( ).toString( );

		find = set_json_object.find( timeKey );
		if( find == end )
			return Result_Var_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 数据失败: %1" ).arg( timeKey ) );
		auto findTime = find.value( ).toString( );

		find = set_json_object.find( idCodeKey );
		if( find == end )
			return Result_Var_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 数据失败: %1" ).arg( idCodeKey ) );
		auto findIdCode = find.value( ).toString( );

		find = set_json_object.find( nameKey );
		if( find == end )
			return Result_Var_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 数据失败: %1" ).arg( nameKey ) );
		auto findName = find.value( ).toString( );

		find = set_json_object.find( singerKey );
		if( find == end )
			return Result_Var_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 数据失败: %1" ).arg( singerKey ) );
		auto findSinger = find.value( ).toString( );
		bool conver;
		this->elapsedTime = findTime.toLongLong( &conver );
		if( conver == false )
			return Result_Var_Messag_Ptr_Out_Args( false, &findTime, toULongLong, tr( "类型转换失败: %1" ).arg( findTime ) );
		this->idCode = findIdCode.toULongLong( &conver );
		if( conver == false )
			return Result_Var_Messag_Ptr_Out_Args( false, &findIdCode, toULongLong, tr( "类型转换失败: %1" ).arg( findIdCode ) );

		this->absoluteFilePath = this->filePath = findFileAbsPath;
		this->name = findName;
		this->singer = findSinger;
		this->elapsedTimeString = DateTimeFormat::millsecondToHourMinSecFrom( this->elapsedTime );
		return true;
	} ) == false )
		return false;
	return true;
}
