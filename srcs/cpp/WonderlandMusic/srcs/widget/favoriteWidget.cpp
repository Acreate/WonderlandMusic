#include "favoriteWidget.h"

#include <QJsonObject>
#include <QMouseEvent>

#include "labelWidget.h"

#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/jsonKey/favoriteWidgetJsonKey.h"
#include "../application/translate/favoriteWidgetTranslate.h"

#include "../mutex/userMutex.h"

#include "../window/playerWindow.h"

FavoriteWidget::FavoriteWidget( QWidget *parent ) : QWidget( parent ) {
}

void FavoriteWidget::deleteFavoriteItem( ) {
	selectFavorite = nullptr;
	size_t count = favoriteVector.size( );
	if( count ) {
		size_t index = 0;
		auto data = favoriteVector.data( );
		for( ; index < count; index += 1 )
			delete data[ index ];
		favoriteVector.clear( );
	}
}

bool FavoriteWidget::deleteResource( ) {
	disconnect( );
	selectFavorite = nullptr;
	deleteFavoriteItem( );
	return true;
}

FavoriteWidget::~FavoriteWidget( ) {
	deleteResource( );
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
	auto appTranslate = AppInstance::getAppInstance( )->getAppDataManage( )->getTranslate( );
	auto translate = appTranslate->getFavoriteWidget( );
	rootFavorite = new LabelWidget( translate->getDefautFavoriteName( ), this );
	return true;
}

bool FavoriteWidget::initAfter( ) {
	rootFavorite->adjustSize( );
	updateLayout( );
	return true;
}

void FavoriteWidget::updateLayout( ) {
	rootFavorite->move( 0, 0 );
	int maxWidth = rootFavorite->width( );
	int maxHeight = rootFavorite->height( );
	size_t count = favoriteVector.size( );
	if( count ) {
		int compWidth;
		int offsetX = 10;
		auto data = favoriteVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 ) {
			data[ index ]->adjustSize( );
			data[ index ]->move( offsetX, maxHeight );
			maxHeight += data[ index ]->height( );
			compWidth = data[ index ]->width( ) + offsetX;
			if( compWidth > maxWidth )
				maxWidth = compWidth;
		}
	}
	resize( maxWidth, maxHeight );
	emit signal_update_layout_over( );
}

bool FavoriteWidget::appendFavoriteItem( const QString &create_favorite_name ) {
	selectFavorite = new LabelWidget( create_favorite_name, this );
	favoriteVector.emplace_back( selectFavorite );
	updateLayout( );
	return true;
}

bool FavoriteWidget::removeFavoriteItem( const QString &remove_favorite_name ) {
	size_t count = favoriteVector.size( );
	if( count ) {
		auto data = favoriteVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( remove_favorite_name == data[ index ]->text( ) ) {
				auto deleteItem = data[ index ];
				favoriteVector.erase( index + favoriteVector.begin( ) );
				if( selectFavorite == deleteItem )
					selectFavorite = nullptr;
				delete deleteItem;
				return true;
			}
	}
	return false;
}

bool FavoriteWidget::resetFavoriteItem( const std::vector< QString > &create_favorite_vector ) {
	deleteFavoriteItem( );
	size_t count = create_favorite_vector.size( );
	if( count ) {
		selectFavorite = nullptr;
		favoriteVector.resize( count );
		auto favoriteData = favoriteVector.data( );
		auto data = create_favorite_vector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			favoriteData[ index ] = new LabelWidget( data[ index ], this );
		updateLayout( );
	}

	return true;
}

LabelWidget * FavoriteWidget::getSelectItem( const QString &name ) const {
	size_t count = favoriteVector.size( );
	if( count ) {
		auto data = favoriteVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->text( ) == name )
				return data[ index ];
	}
	return nullptr;
}

LabelWidget * FavoriteWidget::getSelectItem( const QPoint &pos ) const {
	size_t count = favoriteVector.size( );
	if( count ) {
		auto data = favoriteVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->geometry( ).contains( pos ) )
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
			emit signal_click_favorite_Item( selectFavorite );
			break;
		case Qt::RightButton :
			selectFavorite = getSelectItem( event->pos( ) );
			emit signal_favorite_Item_pop_menu( selectFavorite );
			break;
	}
}
