#include "musicListWidget.h"

#include <QJsonObject>
#include <QPainter>

#include "../musicCentreWidget.h"

#include "../../../../head/release_macro.h"

#include "../../../../mutex/userMutex.h"

#include "../../musicItem/musicItem.h"

MusicListWidget::MusicListWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicListWidget::~MusicListWidget( ) {
	deleteResource( );
}
bool MusicListWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	unsafetyClearMusicItemVector( );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkGreen );
}
void MusicListWidget::setMusicItemInfoVector( const std::vector< MusicItem * > &music_items ) {
	userMutex->lock( );
	unsafetyClearMusicItemVector( );
	this->musicItems = music_items;
	userMutex->unlock( );
}
void MusicListWidget::unsafetyClearMusicItemVector( ) {
}
bool MusicListWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	return true;
}
bool MusicListWidget::init( ) {
	return true;
}
bool MusicListWidget::initAfter( ) {
	return true;
}
bool MusicListWidget::getJsonData( QJsonObject &get_json_object ) const {
	bool result = true;
	userMutex->lock( );
	size_t count = musicItems.size( );
	get_json_object.insert( "count", QString::number( count ) );
	if( count ) {
		QJsonObject arrayJson;
		auto data = musicItems.data( );
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
			get_json_object.insert( "musicItems", arrayJson );
	}
	userMutex->unlock( );
	return result;
}
bool MusicListWidget::setJsonData( const QJsonObject &set_json_object ) {
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

	find = set_json_object.find( "musicItems" );
	if( end == find )
		return false;
	auto musicWindow = musicCentreWidget->getMusicWindow( );
	auto jsonObject = find->toObject( );
	if( jsonObject.size( ) != count )
		return false;
	if( count == 0 ) {
		clearMusicItemVector( );
		return true;
	}
	std::vector< MusicItem * > jsonDataConverMusicItems( count, nullptr );
	auto data = jsonDataConverMusicItems.data( );
	auto iterator = jsonObject.begin( );
	auto endIt = jsonObject.end( );
	size_t index;
	MusicItem *musicItem;
	QString jsonKey;
	for( ; iterator != endIt; ++iterator ) {
		musicItem = new MusicItem( musicWindow );
		jsonKey = iterator.key( );
		if( jsonKey.isEmpty( ) ) {
			ok = false;
			break;
		}
		index = jsonKey.toULongLong( &ok );
		if( ok == false )
			break;
		if( index >= count ) {
			ok = false;
			break;
		}
		data[ index ] = musicItem;
		auto jsonValue = iterator.value( );
		auto jsonValueRefs = jsonValue.toObject( );
		if( musicItem->setJsonData( jsonValueRefs ) == false ) {
			ok = false;
			break;
		}
	}
	// 如果数据正确，则回复数据
	if( ok )
		setMusicItemInfoVector( jsonDataConverMusicItems );
	else
		for( index = 0; index < count; index += 1 )
			if( data[ index ] )
				delete data[ index ];
	return ok;
}
bool MusicListWidget::updateItem( MusicItem *music_item ) {
	return false;
}
bool MusicListWidget::removeItem( MusicItem *music_item ) {
	return false;
}
MusicCentreWidget * MusicListWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
void MusicListWidget::clearMusicItemVector( ) {
	userMutex->lock( );
	unsafetyClearMusicItemVector( );
	userMutex->unlock( );
}
