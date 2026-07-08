#include "favoriteWidget.h"
#include <QJsonObject>
#include <QMouseEvent>
#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/jsonKey/favoriteWidgetJsonKey.h"
#include "../item/favoriteItem.h"
#include "../itemWidget/favoriteItemWidget.h"
#include "../mutex/userMutex.h"

FavoriteWidget::FavoriteWidget( QWidget *parent ) : QWidget( parent ) {
}

bool FavoriteWidget::deleteResource( ) {
	disconnect( );
	selectFavorite = nullptr;
	favoriteVector.clear( );
	return true;
}

FavoriteWidget::~FavoriteWidget( ) {
	deleteResource( );
}

void FavoriteWidget::updateAppMusicManageInof( const std::vector< FavoriteItem * > &vector ) {
	size_t count = vector.size( );
	favoriteVector.resize( count );
	if( count == 0 )
		return;
	auto vectorData = vector.data( );
	auto favoriteData = favoriteVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		favoriteData[ index ] = vectorData[ index ];
		FavoriteItemWidget *itemWidget = favoriteData[ index ]->getFavoriteItemWidget( );
		itemWidget->setParent( this );
		itemWidget->show( );
	}
	emit signal_update_item_over( );
	updateLayout( );
}

bool FavoriteWidget::getJsonData( QJsonObject &get_json_object ) const {
	auto appDataJsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( );
	auto jsonKey = appDataJsonKey->getFavoriteWidget( );

	QJsonObject jsonObject;
	jsonObject.insert( jsonKey->getWidth( ), this->width( ) );
	jsonObject.insert( jsonKey->getHeight( ), this->height( ) );
	get_json_object.insert( jsonKey->getObjectName( ), jsonObject );
	return true;
}

bool FavoriteWidget::setJsonData( const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;
	auto appDataJsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( );
	auto jsonKey = appDataJsonKey->getFavoriteWidget( );
	auto find = set_json_object.find( jsonKey->getObjectName( ) );
	auto end = set_json_object.end( );
	if( find == end )
		return false;

	auto jsonObject = find.value( ).toObject( );
	end = jsonObject.end( );
	qint64 width = this->width( );
	qint64 height = this->height( );
	find = jsonObject.find( jsonKey->getWidth( ) );
	if( find != end )
		width = find.value( ).toInteger( );
	find = jsonObject.find( jsonKey->getHeight( ) );
	if( find != end )
		height = find.value( ).toInteger( );
	resize( width, height );
	adjustSize( );
	return true;
}

bool FavoriteWidget::init( ) {
	deleteResource( );
	return true;
}

bool FavoriteWidget::initBefore( ) {
	deleteResource( );
	return true;
}

bool FavoriteWidget::initAfter( ) {
	updateLayout( );
	return true;
}

void FavoriteWidget::updateLayout( ) {
	int maxWidth = 0;
	int maxHeight = 0;
	size_t count = favoriteVector.size( );
	if( count ) {
		int compWidth;
		int offsetX = 10;
		auto data = favoriteVector.data( );

		size_t index = 0;

		auto favoriteItemWidget = data[ index ]->getFavoriteItemWidget( );
		favoriteItemWidget->adjustSize( );
		favoriteItemWidget->move( 0, maxHeight );
		maxHeight += favoriteItemWidget->height( );
		compWidth = favoriteItemWidget->width( ) + offsetX;
		if( compWidth > maxWidth )
			maxWidth = compWidth;

		for( index = 1; index < count; index += 1 ) {
			favoriteItemWidget = data[ index ]->getFavoriteItemWidget( );
			favoriteItemWidget->adjustSize( );
			favoriteItemWidget->move( offsetX, maxHeight );
			maxHeight += favoriteItemWidget->height( );
			compWidth = favoriteItemWidget->width( ) + offsetX;
			if( compWidth > maxWidth )
				maxWidth = compWidth;
		}
		resize( maxWidth, maxHeight );
		emit signal_update_layout_over( );
	}
}

bool FavoriteWidget::resetFavoriteItem( const std::vector< FavoriteItem * > &favorite_vector ) {
	favoriteVector = favorite_vector;
	return true;
}

FavoriteItem * FavoriteWidget::getSelectItem( const QString &name ) const {
	size_t count = favoriteVector.size( );
	if( count ) {
		auto data = favoriteVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->getFavoriteName( ) == name )
				return data[ index ];
	}
	return nullptr;
}

FavoriteItem * FavoriteWidget::getSelectItem( const QPoint &pos ) const {
	size_t count = favoriteVector.size( );
	if( count ) {
		auto data = favoriteVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->getFavoriteItemWidget( )->geometry( ).contains( pos ) )
				return data[ index ];
	}
	return nullptr;
}

void FavoriteWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}

void FavoriteWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}

void FavoriteWidget::mouseReleaseEvent( QMouseEvent *event ) {
	auto mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			selectFavorite = getSelectItem( event->pos( ) );
			if( selectFavorite )
				emit signal_click_favorite_Item( selectFavorite );
			break;
		case Qt::RightButton :
			selectFavorite = getSelectItem( event->pos( ) );
			if( selectFavorite )
				emit signal_favorite_Item_pop_menu( selectFavorite );
			break;
	}
}
