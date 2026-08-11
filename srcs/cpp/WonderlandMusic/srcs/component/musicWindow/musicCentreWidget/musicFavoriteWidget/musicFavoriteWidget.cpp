#include "musicFavoriteWidget.h"

#include <QJsonObject>
#include <QMouseEvent>
#include <QPainter>

#include "../musicCentreWidget.h"

#include "../../../../application/appRenderImage.h"

#include "../../../../mutex/userMutex.h"

#include "../../../../tools/instanceTools.h"

#include "../../Item/favoriteItem/favoriteItem.h"

#include "../../interface/menu/iMusicFavoriteMenu.h"

#include "../musicListWidget/musicListWidget.h"

MusicFavoriteWidget::MusicFavoriteWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicFavoriteWidget::~MusicFavoriteWidget( ) {
	deleteResource( );
}
bool MusicFavoriteWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	unSafetyClear( );
	musicFavoriteMenu = nullptr;
	userMutex->unlock( );
	return true;
}
void MusicFavoriteWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return;
	if( userMutex == nullptr )
		return;

	QPainter painter( this );

	userMutex->lock( );

	size_t count = favoriteItemVector.size( );
	if( count ) {
		auto renderFont = appRenderImage->getFont( );
		auto fontMetrics = appRenderImage->getFontMetrics( );
		int fontHeight = fontMetrics->height( );
		auto pen = painter.pen( );
		auto font = painter.font( );
		painter.setFont( *renderFont );
		auto data = favoriteItemVector.data( );
		size_t index = 0;
		int offsetY = 0;
		int thisWidgetHeight = this->height( );
		for( ; index < count; index += 1 ) {
			int advance = fontMetrics->horizontalAdvance( data[ index ]->favoriteItemName );
			painter.drawText( QRect( 0, offsetY, advance, fontHeight ), data[ index ]->favoriteItemName );
			offsetY += fontHeight;
			if( offsetY >= thisWidgetHeight )
				break;
		}
		painter.setPen( pen );
		painter.setFont( font );
	}

	userMutex->unlock( );
}
void MusicFavoriteWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	FavoriteItem *favoriteItem = nullptr;
	auto mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::RightButton :
			if( musicFavoriteMenu == nullptr )
				break;
			getPosFavoriteItem( favoriteItem, event->pos( ) );
			musicFavoriteMenu->execMenu( this, favoriteItem, QCursor::pos( ) );
			break;
	}
}
bool MusicFavoriteWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;

	return true;
}
bool MusicFavoriteWidget::init( ) {
	return true;
}
bool MusicFavoriteWidget::initAfter( ) {
	if( createDefaultFavoriteItem( ) == false )
		return false;
	return true;
}
int MusicFavoriteWidget::getSuggestWidth( ) const {
	return suggestWidth;
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
		createDefaultFavoriteItem( );
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
		userMutex->lock( );
		unSafetyClear( );
		favoriteItemVector = jsonDataConverFavoriteItemItems;
		userMutex->unlock( );
		createDefaultFavoriteItem( );
	} else {
		userMutex->lock( );
		for( index = 0; index < count; index += 1 )
			if( data[ index ] ) {
				data[ index ]->musicCentreWidget = nullptr;
				delete data[ index ];
			}
		if( favoriteItem ) {
			favoriteItem->musicCentreWidget = nullptr;
			delete favoriteItem;
		}
		userMutex->unlock( );
		createDefaultFavoriteItem( );
	}
	return ok;
}
bool MusicFavoriteWidget::removeItem( FavoriteItem *favorite_item ) {
	bool result = false;
	userMutex->lock( );
	size_t count = favoriteItemVector.size( );
	if( count > 1 ) {
		auto data = favoriteItemVector.data( );
		size_t index = 1;
		for( ; index < count; index += 1 )
			if( data[ index ] == favorite_item ) {
				auto musicListWidget = musicCentreWidget->getMusicListWidget( );
				auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
				if( currentFavoriteItem == favorite_item ) {
					index -= 1;
					musicListWidget->setCurrentFavoriteItem( data[ index ] );
				}
				favoriteItemVector.erase( favoriteItemVector.begin( ) + index );
				result = true;
				break;
			}
	}
	userMutex->unlock( );
	return result;
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
bool MusicFavoriteWidget::setMusicFavoriteMenu( IMusicFavoriteMenu *music_favorite_menu ) {
	musicFavoriteMenu = music_favorite_menu;
	return true;
}
bool MusicFavoriteWidget::createDefaultFavoriteItem( ) {
	bool result = false;
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	auto fontMetrics = appRenderImage->getFontMetrics( );
	if( fontMetrics == nullptr )
		return false;
	userMutex->lock( );
	size_t count = favoriteItemVector.size( );
	if( count == 0 ) {
		FavoriteItem *favoriteItem = new FavoriteItem( musicCentreWidget, tr( "默认" ) );
		favoriteItemVector.emplace_back( favoriteItem );
		suggestWidth = fontMetrics->horizontalAdvance( favoriteItem->favoriteItemName ) + 5;
		resize( suggestWidth, fontMetrics->height( ) );
		result = true;
	}
	userMutex->unlock( );

	return result;
}

bool MusicFavoriteWidget::getIndexFavoriteItem( FavoriteItem *&result_favorite_item, const size_t &index ) const {
	userMutex->lock( );
	size_t count = favoriteItemVector.size( );
	auto result = count > index;
	if( result )
		result_favorite_item = favoriteItemVector.data( )[ index ];
	userMutex->unlock( );
	return result;
}
bool MusicFavoriteWidget::getPosFavoriteItem( FavoriteItem *&result_favorite_item, const QPoint &widget_local_pos ) const {
	if( contentsRect( ).contains( widget_local_pos ) == false )
		return false;
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	auto fontMetrics = appRenderImage->getFontMetrics( );
	if( fontMetrics == nullptr )
		return false;
	int height = fontMetrics->height( );
	int yPos = widget_local_pos.y( );
	size_t index = yPos / height;
	return getIndexFavoriteItem( result_favorite_item, index );
}
bool MusicFavoriteWidget::getNameFavoriteItem( FavoriteItem *&result_favorite_item, const QString &favorite_item_name ) const {
	auto result = false;
	userMutex->lock( );
	size_t count = favoriteItemVector.size( );
	if( count ) {
		size_t index;
		auto data = favoriteItemVector.data( );
		for( index = 0; index < count; index += 1 )
			if( data[ index ]->favoriteItemName == favorite_item_name ) {
				result = true;
				result_favorite_item = data[ index ];
				break;
			}
	}
	userMutex->unlock( );
	return result;
}
MusicCentreWidget * MusicFavoriteWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
IMusicFavoriteMenu * MusicFavoriteWidget::getMusicFavoriteMenu( ) const {
	return musicFavoriteMenu;
}
FavoriteItem * MusicFavoriteWidget::opendCreateFavoriteItemWidget( ) {
	return nullptr;
}
bool MusicFavoriteWidget::opendRenameFavoriteItemWidget( FavoriteItem *favorite_item ) {
	return false;
}
