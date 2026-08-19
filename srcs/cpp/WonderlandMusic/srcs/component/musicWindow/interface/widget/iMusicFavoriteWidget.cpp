#include "iMusicFavoriteWidget.h"

IMusicFavoriteWidget::IMusicFavoriteWidget( ) {
	appendTypeInfo( this );
}
IMusicFavoriteWidget::~IMusicFavoriteWidget( ) {
}
QString IMusicFavoriteWidget::getTypeName( ) const {
	return typeid( *this ).name( );
}
