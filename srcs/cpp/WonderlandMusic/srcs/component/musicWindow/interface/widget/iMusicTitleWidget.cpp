#include "iMusicTitleWidget.h"
QString IMusicTitleWidget::getTypeName( ) const {
	return typeid( *this ).name( );
}
