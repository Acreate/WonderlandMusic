#include "iMusicListWidget.h"

QString IMusicListWidget::getTypeName( ) const {
	return typeid( *this ).name( );
}
IMusicListWidget::IMusicListWidget( ) {
}
IMusicListWidget::~IMusicListWidget( ) {
}
