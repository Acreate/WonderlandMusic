#include "favoriteItem.h"

#include <QJsonObject>
#include <QPainter>
#include <qfontmetrics.h>

#include <mutex/userMutex.h>

#include "../../../../application/appRenderImage.h"

#include "../../../../dateTimeFormat/dateTimeFormat.h"

#include "../../../../tools/instanceTools.h"

#include "../../musicCentreWidget/musicCentreWidget.h"
#include "../../musicCentreWidget/musicListWidget/musicListWidget.h"
#include "../../musicCentreWidget/musicTitleWidget/musicTitleWidget.h"
#include "../../musicCentreWidget/musicfavoriteWidget/musicfavoriteWidget.h"

#include "../musicItem/musicItem.h"

FavoriteItem::FavoriteItem( MusicCentreWidget *music_centre_widget, const QString &favorite_item_name ) : QObject( music_centre_widget ), musicCentreWidget( music_centre_widget ), favoriteItemName( favorite_item_name ), userMutex( new UserMutex ), drawBuff( new QImage ) {
}
FavoriteItem::~FavoriteItem( ) {
	if( musicCentreWidget ) {
		auto musicListWidget = musicCentreWidget->getMusicFavoriteWidget( );
		if( musicListWidget )
			musicListWidget->removeItem( this );
	}
	setParent( nullptr );
	userMutex->lock( );
	unSafetyClear( );
	userMutex->unlock( );
	delete userMutex;
	delete drawBuff;
}
bool FavoriteItem::getJsonData( QJsonObject &get_json_object ) const {
	bool result = true;
	userMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		QJsonObject arrayJson;
		auto data = musicItemVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 ) {
			QJsonObject itemJsonData;
			if( data[ index ]->getJsonData( itemJsonData ) == false ) {
				result = false;
				break;
			}
			arrayJson.insert( QString::number( index ), itemJsonData );
		}
		if( result ) {
			get_json_object.insert( "FavoriteItem", favoriteItemName );
			get_json_object.insert( "count", QString::number( count ) );
			get_json_object.insert( favoriteItemName, arrayJson );
		}
	}
	userMutex->unlock( );
	return result;
}
bool FavoriteItem::setJsonData( const QJsonObject &set_json_object ) {
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

	find = set_json_object.find( "FavoriteItem" );
	if( end == find )
		return false;
	auto name = find->toString( );

	find = set_json_object.find( name );
	if( end == find )
		return false;
	auto jsonObject = find->toObject( );
	if( jsonObject.size( ) != count )
		return false;
	if( count == 0 ) {
		clear( );
		return true;
	}
	std::vector< MusicItem * > jsonDataConverMusicItems( count, nullptr );
	auto data = jsonDataConverMusicItems.data( );
	auto iterator = jsonObject.begin( );
	auto endIt = jsonObject.end( );
	size_t index;
	MusicItem *musicItem;
	QString jsonKey;
	QJsonObject musicItemJsonObject;
	for( ; iterator != endIt; ++iterator ) {
		musicItemJsonObject = iterator.value( ).toObject( );
		musicItem = new MusicItem( this );
		if( musicItem->setJsonData( musicItemJsonObject ) == false ) {
			delete musicItem;
			ok = false;
			break;
		}
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
	if( ok ) {
		count = musicItemVector.size( );
		data = musicItemVector.data( );
		for( index = 0; index < count; index += 1 )
			if( data[ index ] )
				delete data[ index ];
		musicItemVector = jsonDataConverMusicItems;
		favoriteItemName = name;
	} else
		for( index = 0; index < count; index += 1 )
			if( data[ index ] )
				delete data[ index ];
	return ok;
}
const QString & FavoriteItem::getFavoriteItemName( ) const {
	return favoriteItemName;
}

bool FavoriteItem::unSafetySetMusicItemInfoVector( const std::vector< MusicItem * > &music_items ) {
	if( unSafetyClearInfo( ) == false )
		return false;
	this->musicItemVector = music_items;
	if( unSafetyUpdateInfo( ) == false )
		return false;
	if( unSafetyUpdateShow( ) == false )
		return false;
	return true;
}
bool FavoriteItem::setMusicItemInfoVector( const std::vector< MusicItem * > &music_items ) {
	userMutex->lock( );
	auto result = unSafetySetMusicItemInfoVector( music_items );
	userMutex->unlock( );
	return result;
}
void FavoriteItem::getMusicItemVector( std::vector< MusicItem * > &result_music_item_vector ) {
	userMutex->lock( );
	result_music_item_vector = this->musicItemVector;
	userMutex->unlock( );
}
void FavoriteItem::getMusicItemVector( size_t &result_count, std::vector< MusicItem * > &result_music_item_vector, const std::vector< size_t > &get_index ) {
	result_count = 0;
	size_t getCount = get_index.size( );
	result_music_item_vector.resize( getCount );
	if( getCount == 0 )
		return;
	size_t getDataIndex;
	auto getData = get_index.data( );
	auto setData = result_music_item_vector.data( );
	size_t setDataIndex = 0;
	userMutex->lock( );
	size_t count = this->musicItemVector.size( );
	auto data = this->musicItemVector.data( );
	for( ; setDataIndex < getCount; setDataIndex += 1 )
		if( getDataIndex = getData[ setDataIndex ], getDataIndex < count ) {
			setData[ result_count ] = data[ getDataIndex ];
			result_count += 1;
		}
	userMutex->unlock( );
	if( result_count != getCount )
		result_music_item_vector.resize( result_count );
}
QImage * FavoriteItem::getDrawBuff( ) const {
	return drawBuff;
}

void FavoriteItem::updateItemWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width ) {
	intervalWidth = interval_width;
	separatorWidth = separator_width;
	musicCodeWidth = music_code_width;
	musicNameWidth = music_name_width;
	musicSingerNameWidth = music_singer_name_width;
	musicDurationTimeWidth = music_duration_time_width;
	userMutex->lock( );
	unSafetyUpdateInfo( );
	unSafetyUpdateShow( );
	userMutex->unlock( );
}
bool FavoriteItem::unSafetyClearInfo( ) {
	size_t count = musicItemVector.size( );
	if( count ) {
		if( unSafetyClearShow( ) == false )
			return false;
		auto musicItem = musicItemVector.data( );
		size_t index;
		for( index = 0; index < count; index += 1 ) {
			musicItem[ index ]->favoriteItem = nullptr;
			delete musicItem;
		}
		musicItemVector.clear( );
	}
	return true;
}
bool FavoriteItem::unSafetyClearShow( ) {
	if( unSafetyUpdateInfo( ) == false )
		return false;
	if( unSafetyUpdateShow( ) == false )
		return false;
	return true;
}
bool FavoriteItem::renderImage( size_t index, MusicItem *music_item ) const {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	auto fontMetrics = appRenderImage->getFontMetrics( );
	int fontHeight = fontMetrics->height( );
	QPainter painter;

	QColor fillSeparatorColor = QColor( 255, 255, 255 );
	auto calculateMinWidth = musicCentreWidget->getMusicTitleWidget( )->getCalculateMinWidth( );
	auto font = appRenderImage->getFont( );
	return renderImage( painter, intervalWidth, index, music_item, calculateMinWidth, fontHeight, *font, fillSeparatorColor );
}
bool FavoriteItem::hasMusicFile( const QString &file_path ) const {
	bool result = false;
	userMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		auto data = musicItemVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( result = data[ index ]->absoluteFilePath == file_path, result )
				break;
	}
	userMutex->unlock( );
	return result;
}
bool FavoriteItem::renderImage( QPainter &painter, int intervalWidth, size_t index, MusicItem *music_item, int calculate_min_width, int calculate_height, const QFont &font, const QColor &fill_separator_color ) const {
	music_item->idCode = index;
	if( music_item->rendBuff )
		delete music_item->rendBuff;
	music_item->rendBuff = new QImage( calculate_min_width, calculate_height, QImage::Format_RGB888 );
	music_item->rendBuff->fill( 0 );
	painter.begin( music_item->rendBuff );
	painter.setFont( font );

	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;

	QString text = QString::number( music_item->idCode );
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), text );

	intervalWidth += intervalWidth + musicCodeWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), music_item->name );

	intervalWidth += intervalWidth + musicNameWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), music_item->singer );

	intervalWidth += intervalWidth + musicSingerNameWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculate_height ), music_item->elapsedTimeString );

	intervalWidth += intervalWidth + musicDurationTimeWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculate_height ), fill_separator_color );

	painter.end( );
	return true;
}
bool FavoriteItem::unSafetyUpdateInfo( ) {
	size_t count = musicItemVector.size( );
	if( count == 0 )
		return true;
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	auto fontMetrics = appRenderImage->getFontMetrics( );
	int fontHeight = fontMetrics->height( );
	QPainter painter;
	QColor fillSeparatorColor = QColor( 255, 255, 255 );
	QString text;
	int calculateMinWidth;
	const QFont *font;
	MusicItem **data;
	size_t index;
	calculateMinWidth = musicCentreWidget->getMusicTitleWidget( )->getCalculateMinWidth( );
	font = appRenderImage->getFont( );
	data = musicItemVector.data( );
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->favoriteItem = this, data[ index ]->favoriteItem == nullptr )
			return false;
		else if( data[ index ]->rendBuff == nullptr ) {
			renderImage( painter, intervalWidth, index, data[ index ], calculateMinWidth, fontHeight, *font, fillSeparatorColor );
		} else if( data[ index ]->idCode != index ) {
			if( data[ index ]->rendBuff->width( ) != calculateMinWidth || data[ index ]->rendBuff->height( ) != fontHeight ) {
				data[ index ]->rendBuff = new QImage( calculateMinWidth, fontHeight, QImage::Format_RGB888 );
				data[ index ]->rendBuff->fill( 0 );
				renderImage( painter, intervalWidth, index, data[ index ], calculateMinWidth, fontHeight, *font, fillSeparatorColor );
				continue;
			}
			data[ index ]->idCode = index;
			painter.begin( data[ index ]->rendBuff );
			painter.setFont( *font );

			intervalWidth += intervalWidth + separatorWidth;
			text = QString::number( data[ index ]->idCode );
			painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, fontHeight ), text );
		}

	return true;
}
bool FavoriteItem::unSafetyUpdateShow( ) {
	size_t count = musicItemVector.size( );
	if( count == 0 ) {
		*drawBuff = QImage( );
		return true;
	}
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	int drawBuffHeight = drawBuff->height( );
	auto fontMetrics = appRenderImage->getFontMetrics( );
	int fontHeight = fontMetrics->height( );
	int imageHeight = fontHeight * count;
	QPainter painter;
	int offsetX;
	int offsetY;

	int calculateMinWidth;
	MusicItem **data = musicItemVector.data( );
	size_t index;
	if( imageHeight != drawBuffHeight ) {
		calculateMinWidth = musicCentreWidget->getMusicTitleWidget( )->getCalculateMinWidth( );
		*drawBuff = QImage( calculateMinWidth, imageHeight, QImage::Format_RGB888 );
		drawBuff->fill( 0 );
	}
	offsetX = 0;
	offsetY = 0;
	painter.begin( drawBuff );
	for( index = 0; index < count; index += 1 ) {
		painter.drawImage( offsetX, offsetY, *data[ index ]->rendBuff );
		offsetY += fontHeight;
	}
	painter.end( );
	return true;
}
bool FavoriteItem::unSafetyRepaint( ) {
	if( musicCentreWidget == nullptr )
		return false;
	MusicListWidget *musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	musicListWidget->repaint( );
	return true;
}
bool FavoriteItem::unSafetyUpdatePaint( ) {
	if( musicCentreWidget == nullptr )
		return false;
	MusicListWidget *musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	musicListWidget->update( );
	return true;
}
void FavoriteItem::unSafetyClear( ) {
	auto count = musicItemVector.size( );
	auto data = musicItemVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ] )
			delete data[ index ];
	musicItemVector.clear( );
}
bool FavoriteItem::unSafetyUpdateItem( MusicItem *music_item ) {
	size_t index;
	if( unSafetyHasItem( index, music_item ) == false )
		return false;
	auto data = musicItemVector.data( );
	if( renderImage( index, data[ index ] ) == false )
		return false;
	unSafetyUpdateShow( );
	return true;
}
bool FavoriteItem::unSafetyRemoveItem( MusicItem *music_item ) {
	size_t index;
	if( hasMusicItem( index, music_item ) == false )
		return false;
	auto iterator = musicItemVector.begin( ) + index;
	MusicItem *removeTarget = *iterator;
	musicItemVector.erase( iterator );
	removeTarget->favoriteItem = nullptr;
	unSafetyUpdateInfo( );
	unSafetyUpdateShow( );
	return true;
}
bool FavoriteItem::unSafetyHasItem( size_t &result_index, const MusicItem *music_item ) const {
	bool cond = false;
	if( music_item->favoriteItem != this )
		return cond;
	size_t count = musicItemVector.size( );
	if( count == 0 )
		return false;
	auto musicItem = musicItemVector.data( );
	for( result_index = 0; result_index < count; result_index += 1 )
		if( cond = musicItem[ result_index ] == music_item, cond )
			break;
	return cond;
}
bool FavoriteItem::unSafetyAddItem( MusicItem *music_item ) {
	size_t index;
	if( unSafetyHasItem( index, music_item ) == true )
		return unSafetyUpdateItem( music_item );
	// 删除就有的项
	if( music_item->favoriteItem ) {
		if( music_item->favoriteItem != this ) {
			bool removeItem = music_item->favoriteItem->removeMusicItem( music_item );
			if( removeItem == false )
				return false;
		}
	}
	// 添加到该列表
	music_item->favoriteItem = this;
	musicItemVector.emplace_back( music_item );
	unSafetyUpdateInfo( );
	unSafetyUpdateShow( );
	return true;
}
bool FavoriteItem::updateInfo( ) {
	userMutex->lock( );
	auto result = unSafetyUpdateInfo( );
	userMutex->unlock( );
	unSafetyRepaint( );
	return result;
}
bool FavoriteItem::updateShow( ) {
	userMutex->lock( );
	auto result = unSafetyUpdateShow( );
	userMutex->unlock( );
	unSafetyRepaint( );
	return result;
}
void FavoriteItem::clear( ) {
	userMutex->lock( );
	unSafetyClear( );
	userMutex->unlock( );
	unSafetyRepaint( );
}
bool FavoriteItem::hasMusicItem( size_t &result_index, const MusicItem *music_item ) const {
	userMutex->lock( );
	bool cond = unSafetyHasItem( result_index, music_item );
	userMutex->unlock( );
	return cond;
}
bool FavoriteItem::addMusicItem( MusicItem *music_item ) {
	userMutex->lock( );
	auto result = unSafetyAddItem( music_item );
	userMutex->unlock( );
	unSafetyRepaint( );
	return result;
}

bool FavoriteItem::updateMusicItem( MusicItem *music_item ) {
	userMutex->lock( );
	bool safetyRemoveItem = unSafetyUpdateItem( music_item );
	userMutex->unlock( );
	if( safetyRemoveItem == false )
		return false;
	unSafetyRepaint( );
	return safetyRemoveItem;
}
bool FavoriteItem::removeMusicItem( MusicItem *music_item ) {
	userMutex->lock( );
	bool safetyRemoveItem = unSafetyRemoveItem( music_item );
	userMutex->unlock( );
	if( safetyRemoveItem == false )
		return false;
	userMutex->lock( );
	unSafetyUpdateInfo( );
	unSafetyClearShow( );
	userMutex->unlock( );
	unSafetyRepaint( );
	return safetyRemoveItem;
}
