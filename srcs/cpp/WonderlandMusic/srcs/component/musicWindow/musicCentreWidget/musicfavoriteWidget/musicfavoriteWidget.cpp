#include "musicFavoriteWidget.h"

#include <QJsonObject>
#include <QPainter>

#include "../musicCentreWidget.h"

#include "../../../../head/after_init_macro.h"
#include "../../../../head/before_init_macro.h"
#include "../../../../head/create_ptr_macro.h"
#include "../../../../head/init_macro.h"

#include "../../../../mutex/userMutex.h"

#include "../../Item/favoriteItem/favoriteItem.h"

#include "../../musicLoad/musicLoad.h"
MusicFavoriteWidget::MusicFavoriteWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicFavoriteWidget::~MusicFavoriteWidget( ) {
	deleteResource( );
}
bool MusicFavoriteWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	MusicLoadTools::setMusicListWidget( musicLoad, nullptr );
	MusicLoadTools::releaseMusicLoad( &musicLoad );
	userMutex->unlock( );
	return true;
}
void MusicFavoriteWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkBlue );
}
bool MusicFavoriteWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;

	if( MusicLoadTools::createMusicLoad( &this->musicLoad, musicCentreWidget ) == false ) {
		Create_Ptr_Resource_App_Core_Message_String_Ptr( this->musicLoad );
		if( this->musicLoad ) {
			MusicLoadTools::setMusicListWidget( this->musicLoad, nullptr );
			MusicLoadTools::releaseMusicLoad( &this->musicLoad );
		}
		this->musicLoad = nullptr;
		return false;
	}
	Before_Init_Resource_App_Core_Ptr( musicLoad );
	return true;
}
bool MusicFavoriteWidget::init( ) {
	Init_Resource_App_Core_Ptr( musicLoad );
	return true;
}
bool MusicFavoriteWidget::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicLoad );
	return true;
}
int MusicFavoriteWidget::getSuggestWidth( ) const {
	return 50;
}
bool MusicFavoriteWidget::getJsonData( QJsonObject &get_json_object ) const {
	bool result = true;
	userMutex->lock( );
	size_t count = favoriteItemVector.size( );
	get_json_object.insert( "count", QString::number( count ) );
	if( count ) {
		QJsonObject arrayJson;
		auto data = favoriteItemVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 ) {
			QJsonObject itemJsonData;
			if( data[ index ]->getJsonData( itemJsonData ) == false ) {
				result = false;
				break;
			}
			arrayJson.insert( QString::number( index ), itemJsonData );
		}
		if( result )
			get_json_object.insert( "favoriteItemVector", arrayJson );
	}
	userMutex->unlock( );
	return result;
}
bool MusicFavoriteWidget::setJsonData( const QJsonObject &set_json_object ) {
	auto end = set_json_object.end( );
	QJsonObject::const_iterator find;
	find = set_json_object.find( "count" );
	if( end == find )
		return false;

	auto string = find->toString( );
	bool ok;
	auto count = string.toULongLong( &ok );
	if( ok == false )
		return false;

	find = set_json_object.find( "favoriteItemVector" );
	if( end == find )
		return false;
	auto jsonObject = find->toObject( );
	if( jsonObject.size( ) != count )
		return false;
	if( count == 0 ) {
		userMutex->lock( );
		unSafetyClear( );
		userMutex->unlock( );
		repaint( );
		return true;
	}
	std::vector< FavoriteItem * > jsonDataConverFavoriteItemItems( count, nullptr );
	auto data = jsonDataConverFavoriteItemItems.data( );
	auto iterator = jsonObject.begin( );
	auto endIt = jsonObject.end( );
	size_t index;
	FavoriteItem *favoriteItem = nullptr;
	QString jsonKey;
	QJsonObject musicItemJsonObject;
	for( ; iterator != endIt; ++iterator ) {
		jsonKey = iterator.key( );
		if( ok = jsonKey.isEmpty( ), ok == true )
			break; // 空
		index = jsonKey.toULongLong( &ok );
		if( ok == false )
			break; // 转换失败
		if( ok = index >= count, ok == false )
			break; // 下标溢出
		auto jsonValue = iterator.value( );
		auto jsonValueRefs = jsonValue.toObject( );
		favoriteItem = new FavoriteItem( musicCentreWidget, "" );
		if( ok = favoriteItem->setJsonData( jsonValueRefs ), ok == false )
			break; // 数据无法恢复
		data[ index ] = favoriteItem;
	}
	// 如果数据正确，则回复数据
	if( ok ) {
		unSafetyClear( );
		favoriteItemVector = jsonDataConverFavoriteItemItems;
	} else {
		for( index = 0; index < count; index += 1 )
			if( data[ index ] ) {
				data[ index ]->musicCentreWidget = nullptr;
				delete data[ index ];
			}
		if( favoriteItem ) {
			favoriteItem->musicCentreWidget = nullptr;
			delete favoriteItem;
		}
	}
	return ok;
}
bool MusicFavoriteWidget::removeItem( FavoriteItem *favorite_item ) {
	size_t count = favoriteItemVector.size( );
	auto data = favoriteItemVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == favorite_item ) {
			favoriteItemVector.erase( favoriteItemVector.begin( ) + index );
			return true;
		}
	return false;
}
bool MusicFavoriteWidget::unSafetyClear( ) {
	size_t count = favoriteItemVector.size( );
	if( count == 0 )
		return true;
	auto data = favoriteItemVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 ) {
		data[ index ]->musicCentreWidget = nullptr;
		delete data[ index ];
	}
	favoriteItemVector.clear( );
	return true;
}

bool MusicFavoriteWidget::loadMusicFile( const QString &music_file_path ) {
	return musicLoad->loadMusicFile( music_file_path );
}
bool MusicFavoriteWidget::loadMusicDir( const QString &music_dir_path ) {
	return musicLoad->loadMusicDir( music_dir_path );
}
MusicLoad * MusicFavoriteWidget::getMusicLoad( ) const {
	return musicLoad;
}
bool MusicFavoriteWidget::removeMusicLoad( MusicLoad *music_load ) {
	bool resultBool = false;
	if( this->musicLoad != nullptr ) {
		if( music_load != this->musicLoad )
			return resultBool;
		resultBool = true;
	} else if( music_load == nullptr )
		resultBool = true;
	// 判定是否继续
	if( resultBool == false )
		return resultBool;

	if( MusicLoadTools::createMusicLoad( &this->musicLoad, musicCentreWidget ) == false ) {
		Create_Ptr_Resource_App_Core_Message_String_Ptr( this->musicLoad );
		this->musicLoad = music_load;
		return false;
	}
	if( musicLoad->initBefore( ) == false ) {
		Before_Init_Resource_App_Core_Message_String_Ptr( musicLoad );
		this->musicLoad = music_load;
		return false;
	}
	if( musicLoad->init( ) == false ) {
		Init_Resource_App_Core_Message_String_Ptr( musicLoad );
		this->musicLoad = music_load;
		return false;
	}
	if( musicLoad->initAfter( ) == false ) {
		After_Init_Resource_App_Core_Message_String_Ptr( musicLoad );
		this->musicLoad = music_load;
		return false;
	}
	return true;
}
