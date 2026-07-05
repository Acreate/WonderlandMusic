#include "favoriteWidget.h"
#include "favoriteWidget.h"

#include "labelWidget.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
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
	setFixedSize( maxWidth, maxHeight );
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

void FavoriteWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}

void FavoriteWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}

void FavoriteWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}
