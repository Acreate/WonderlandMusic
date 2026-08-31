#include "iMusicFavoriteItemWidget.h"

#include <QRect>
#include <qpoint.h>
IMusicFavoriteItemWidget::IMusicFavoriteItemWidget( ) {
	appendTypeInfo( this );
}
IMusicFavoriteItemWidget::~IMusicFavoriteItemWidget( ) {
}
bool IMusicFavoriteItemWidget::getGeometry( QRect &result_geometry ) const {
	int x, y, width, height;
	if( getPos( x, y ) == false )
		return false;
	if( getSize( width, height ) == false )
		return false;
	result_geometry = QRect( x, y, width, height );
	return true;
}
bool IMusicFavoriteItemWidget::setGeometry( const QRect &set_geometry ) {
	if( setPos( set_geometry.x( ), set_geometry.y( ) ) == false )
		return false;
	if( setSize( set_geometry.width( ), set_geometry.height( ) ) == false )
		return false;
	return true;
}
