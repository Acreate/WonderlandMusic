#include "iMusicFavoriteWidget.h"
QString IMusicFavoriteWidget::getTypeName( ) const {
	return typeid( *this ).name( );
}
