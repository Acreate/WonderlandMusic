#include "iMusicCentreWidget.h"

#include "../info/iMusicWidgetSizeInfo.h"
int IMusicCentreWidget::setFavoriteWidth( const int &favoriet_width ) {
	auto musicWidgetSizeInfo = getMusicWidgetSizeInfo( );
	if( musicWidgetSizeInfo == nullptr )
		return 0;
	return musicWidgetSizeInfo->setFavoriteWidth( favoriet_width );
}
int IMusicCentreWidget::setTitleHeight( const int &title_height ) {
	auto musicWidgetSizeInfo = getMusicWidgetSizeInfo( );
	if( musicWidgetSizeInfo == nullptr )
		return 0;
	return musicWidgetSizeInfo->setTitleHeight( title_height );
}
IMusicCentreWidget::IMusicCentreWidget( ) {
	appendTypeInfo( this );
}
