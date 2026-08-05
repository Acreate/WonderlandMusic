#include "musicTitleWidget.h"

#include <QPainter>

#include "../musicCentreWidget.h"

#include "../../../../application/appRenderImage.h"

#include "../../../../tools/instanceTools.h"
MusicTitleWidget::MusicTitleWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteResource( );
}
bool MusicTitleWidget::deleteResource( ) {
	return true;
}
void MusicTitleWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkYellow );
}
bool MusicTitleWidget::initBefore( ) {
	return true;
}
bool MusicTitleWidget::init( ) {
	return true;
}
bool MusicTitleWidget::initAfter( ) {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	suggestHeight = appRenderImage->getFontMetrics( )->height( );

	return true;
}
int MusicTitleWidget::getSuggestHeight( ) const {
	return suggestHeight;
}
