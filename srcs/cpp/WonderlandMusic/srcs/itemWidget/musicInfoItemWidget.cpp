#include "musicInfoItemWidget.h"

#include <QPainter>

#include "../application/appInstance.h"
#include "../application/renderImage.h"

#include "../widget/playListWidget.h"

MusicInfoItemWidget::MusicInfoItemWidget( PlayListWidget *parent ) : QWidget( parent ), MusicInfoItem( parent ) {
	splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
}

void MusicInfoItemWidget::paintEvent( QPaintEvent *event ) {
	auto font = AppInstance::getAppInstance( )->getRenderImage( )->getFont( );

	int offsetSplitX = splitWidth / 2;
	QPainter painter;
	painter.begin( this );
	auto pen = painter.pen( );
	pen.setWidth( splitWidth );
	painter.setPen( pen );
	painter.setFont( *font );

	int drawOffsetX = offsetSplitX + widgetBeforeWidth;
	QRect drawRect;
	auto currentHeight = height( );
	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicNameWidth, currentHeight ) );
	painter.drawText( drawRect, musicName );
	drawOffsetX += musicNameWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicSingerWidth, currentHeight ) );
	painter.drawText( drawRect, musicSinger );
	drawOffsetX += musicSingerWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicDurationWidth, currentHeight ) );
	painter.drawText( drawRect, formatStringDuration );
	drawOffsetX += musicDurationWidth + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentHeight );

	painter.end( );
}
