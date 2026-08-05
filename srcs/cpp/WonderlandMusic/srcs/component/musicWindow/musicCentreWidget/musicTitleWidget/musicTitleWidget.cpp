#include "musicTitleWidget.h"

#include <QPainter>

#include "../musicCentreWidget.h"

#include "../../../../application/appRenderImage.h"
#include "../../../../application/translate/musicTitleWidgetTranslate.h"

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

	AppTranslateTools::getMusicTitleWidget( [this] ( MusicTitleWidgetTranslate &translate ) {
		auto appRenderImage = InstanceTools::getAppRenderImage( );
		if( appRenderImage == nullptr )
			return;
		auto font = appRenderImage->getFont( );
		auto fillSeparatorColor = Qt::GlobalColor::black;
		QPainter painter( this );
		painter.setFont( *font );
		auto pen = painter.pen( );
		pen.setColor( fillSeparatorColor );
		painter.setPen( pen );
		auto &musicCode = translate.getMusicCode( );
		int offsetX = intervalWidth;
		int offsetY = 0;

		painter.drawText( QRect( offsetX, offsetY, musicCodeWidth, suggestHeight ), musicCode );

		offsetX += intervalWidth + musicCodeWidth;
		painter.fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );

		offsetX += intervalWidth + separatorWidth;
		auto &musicName = translate.getMusicName( );
		painter.drawText( QRect( offsetX, offsetY, musicCodeWidth, suggestHeight ), musicName );

		offsetX += intervalWidth + musicNameWidth;
		painter.fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );

		offsetX += intervalWidth + separatorWidth;
		auto &musicSingeName = translate.getMusicSingeName( );
		painter.drawText( QRect( offsetX, offsetY, musicCodeWidth, suggestHeight ), musicSingeName );

		offsetX += intervalWidth + musicSingerNameWidth;
		painter.fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );

		offsetX += intervalWidth + separatorWidth;
		auto &musicDurationTime = translate.getMusicDurationTime( );
		painter.drawText( QRect( offsetX, offsetY, musicCodeWidth, suggestHeight ), musicDurationTime );

		offsetX += intervalWidth + musicDurationTimeWidth;
		painter.fillRect( QRect( offsetX, offsetY, separatorWidth, suggestHeight ), fillSeparatorColor );
	} );
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
	auto fontMetrics = appRenderImage->getFontMetrics( );
	suggestHeight = fontMetrics->height( );
	separatorWidth = 5;
	intervalWidth = 2;
	if( AppTranslateTools::getMusicTitleWidget( [this,&fontMetrics] ( MusicTitleWidgetTranslate &translate ) {
		musicCodeWidth = fontMetrics->horizontalAdvance( translate.getMusicCode( ) );
		musicNameWidth = fontMetrics->horizontalAdvance( translate.getMusicName( ) );
		musicSingerNameWidth = fontMetrics->horizontalAdvance( translate.getMusicSingeName( ) );
		musicDurationTimeWidth = fontMetrics->horizontalAdvance( translate.getMusicDurationTime( ) );
	} ) == false )
		return false;
	int offsetX = intervalWidth * 8 + separatorWidth * 3 + musicCodeWidth + musicNameWidth + musicSingerNameWidth + musicDurationTimeWidth;
	setMinimumWidth( offsetX );
	return true;
}
int MusicTitleWidget::getSuggestHeight( ) const {
	return suggestHeight;
}
