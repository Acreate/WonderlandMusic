#include "musicListWidget.h"

#include <QJsonObject>
#include <QPainter>

#include "../musicCentreWidget.h"

#include "../../musicWindow.h"

#include "../../../../application/appRenderImage.h"

#include "../../../../dateTimeFormat/dateTimeFormat.h"

#include "../../../../head/release_macro.h"

#include "../../../../mutex/userMutex.h"

#include "../../../../tools/instanceTools.h"

#include "../../musicItem/musicItem.h"

#include "../musicTitleWidget/musicTitleWidget.h"

MusicListWidget::MusicListWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicListWidget::~MusicListWidget( ) {
	deleteResource( );
}
bool MusicListWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	unSafetyClear( );
	Delete_Resource_App_Core_Ptr( drawBuff );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkGreen );

	if( drawBuff == nullptr )
		return;
	if( userMutex == nullptr )
		return;
	if( userMutex->tryLock( ) == false )
		return;
	painter.drawImage( 0, 0, *drawBuff );
	userMutex->unlock( );
}
void MusicListWidget::setMusicItemInfoVector( const std::vector< MusicItem * > &music_items ) {
	userMutex->lock( );
	unSafetyClearInfo( );
	this->musicItemVector = music_items;
	unSafetyUpdateInfo( );
	unSafetyUpdateShow( );
	userMutex->unlock( );
}
bool MusicListWidget::unSafetyClearInfo( ) {
	size_t count = musicItemVector.size( );
	if( count ) {
		if( unSafetyClearShow( ) == false )
			return false;
		auto musicItem = musicItemVector.data( );
		size_t index;
		for( index = 0; index < count; index += 1 ) {
			musicItem[ index ]->musicWindow = nullptr;
			delete musicItem;
		}
		musicItemVector.clear( );
	}
	return true;
}
bool MusicListWidget::unSafetyClearShow( ) {
	userMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count == 0 ) {
		*drawBuff = QImage( );
	} else {
		auto appRenderImage = InstanceTools::getAppRenderImage( );
		if( appRenderImage ) {
			int drawBuffHeight = drawBuff->height( );
			auto fontMetrics = appRenderImage->getFontMetrics( );
			int fontHeight = fontMetrics->height( );
			int imageHeight = fontHeight * count;
			if( imageHeight != drawBuffHeight ) {
				int calculateMinWidth = musicCentreWidget->getMusicTitleWidget( )->getCalculateMinWidth( );
				*drawBuff = QImage( calculateMinWidth, imageHeight, QImage::Format_RGB888 );
				drawBuff->fill( 0 );

				QPainter painter;
				auto font = appRenderImage->getFont( );
				auto data = musicItemVector.data( );
				size_t index = 0;
				QColor fillSeparatorColor = QColor( 255, 255, 255 );
				QString text;
				int offsetX = intervalWidth;
				int offsetY = 0;
				for( ; index < count; index += 1 )
					if( data[ index ]->rendBuff == nullptr ) {
						data[ index ]->rendBuff = new QImage( calculateMinWidth, fontHeight, QImage::Format_RGB888 );
						data[ index ]->rendBuff->fill( 0 );
						painter.begin( data[ index ]->rendBuff );
						painter.setFont( *font );

						painter.fillRect( QRect( offsetX, offsetY, separatorWidth, fontHeight ), fillSeparatorColor );

						offsetX += intervalWidth + separatorWidth;

						text = QString::number( data[ index ]->idCode );
						painter.drawText( QRect( offsetX, offsetY, musicCodeWidth, fontHeight ), text );

						offsetX += intervalWidth + musicCodeWidth;
						painter.fillRect( QRect( offsetX, offsetY, separatorWidth, fontHeight ), fillSeparatorColor );

						offsetX += intervalWidth + separatorWidth;
						painter.drawText( QRect( offsetX, offsetY, musicCodeWidth, fontHeight ), data[ index ]->name );

						offsetX += intervalWidth + musicNameWidth;
						painter.fillRect( QRect( offsetX, offsetY, separatorWidth, fontHeight ), fillSeparatorColor );

						offsetX += intervalWidth + separatorWidth;
						painter.drawText( QRect( offsetX, offsetY, musicCodeWidth, fontHeight ), data[ index ]->singer );

						offsetX += intervalWidth + musicSingerNameWidth;
						painter.fillRect( QRect( offsetX, offsetY, separatorWidth, fontHeight ), fillSeparatorColor );

						text = DateTimeFormat::millsecondToHourMinSecFrom( data[ index ]->elapsedTime );
						offsetX += intervalWidth + separatorWidth;
						painter.drawText( QRect( offsetX, offsetY, musicCodeWidth, fontHeight ), text );

						offsetX += intervalWidth + musicDurationTimeWidth;
						painter.fillRect( QRect( offsetX, offsetY, separatorWidth, fontHeight ), fillSeparatorColor );

						painter.end( );
					}
				offsetX = 0;
				offsetY = 0;
				painter.begin( drawBuff );
				for( index = 0; index < count; index += 1 ) {
					painter.drawImage( offsetX, offsetY, *data[ index ]->rendBuff );
					offsetY += fontHeight;
				}
				painter.end( );
			}
		}
	}
	userMutex->unlock( );
	return true; // todo : 清理显示
}
bool MusicListWidget::unSafetyUpdateInfo( ) {
	return true; // todo : 更新信息
}
bool MusicListWidget::unSafetyUpdateShow( ) {
	return true; // todo : 更新显示缓存-不更新窗口
}
void MusicListWidget::unSafetyClear( ) {
	unSafetyClearShow( );
	unSafetyClearInfo( );
}
bool MusicListWidget::updateInfo( ) {
	userMutex->lock( );
	auto result = unSafetyUpdateInfo( );
	userMutex->unlock( );
	return result;
}
bool MusicListWidget::updateShow( ) {
	userMutex->lock( );
	auto result = unSafetyUpdateShow( );
	userMutex->unlock( );
	return result;
}
void MusicListWidget::clear( ) {
	userMutex->lock( );
	unSafetyClear( );
	userMutex->unlock( );
}
bool MusicListWidget::hasItem( size_t &result_index, const MusicItem *music_item ) const {
	bool cond = false;
	if( music_item->musicWindow != musicCentreWidget->getMusicWindow( ) )
		return cond;
	userMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		auto musicItem = musicItemVector.data( );
		for( result_index = 0; result_index < count; result_index += 1 )
			if( cond = musicItem[ result_index ] == music_item, cond )
				break;
	}
	userMutex->unlock( );
	return cond;
}
bool MusicListWidget::addItem( MusicItem *music_item ) {
	size_t index;
	if( hasItem( index, music_item ) == true )
		return updateItem( music_item );
	// 删除就有的项
	if( music_item->musicWindow ) {
		bool removeItem = music_item->musicWindow->removeItem( music_item );
		if( removeItem == false )
			return false;
	}
	userMutex->lock( );
	music_item->musicWindow = musicCentreWidget->getMusicWindow( );
	musicItemVector.emplace_back( music_item );
	userMutex->unlock( );
	return true;
}
void MusicListWidget::updateItemWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width ) {
	int calculateMinWidth = music_title_widget->getCalculateMinWidth( );
	resize( calculateMinWidth, height( ) );
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
	repaint( );
}
bool MusicListWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	drawBuff = new QImage;
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
	size_t count = musicItemVector.size( );
	get_json_object.insert( "count", QString::number( count ) );
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
		musicItem = new MusicItem( musicWindow );
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
	if( ok )
		setMusicItemInfoVector( jsonDataConverMusicItems );
	else
		for( index = 0; index < count; index += 1 )
			if( data[ index ] )
				delete data[ index ];
	return ok;
}
bool MusicListWidget::updateItem( MusicItem *music_item ) {
	if( music_item->musicWindow != musicCentreWidget->getMusicWindow( ) )
		return false;
	return true; // todo : 更新项信息
}
bool MusicListWidget::removeItem( MusicItem *music_item ) {
	if( music_item->musicWindow != musicCentreWidget->getMusicWindow( ) )
		return false;
	size_t index;
	if( hasItem( index, music_item ) == false )
		return false;
	userMutex->lock( );
	auto iterator = musicItemVector.begin( ) + index;
	MusicItem *removeTarget = *iterator;
	musicItemVector.erase( iterator );
	userMutex->unlock( );
	updateInfo( );
	updateShow( );
	removeTarget->musicWindow = nullptr;
	return true;
}
MusicCentreWidget * MusicListWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
