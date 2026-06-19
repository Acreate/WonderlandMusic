#include "musicInfoItemWidget.h"

#include <QPainter>

#include "../application/appInstance.h"
#include "../application/renderImage.h"

#include "../widget/playerListWidget.h"

MusicInfoItemWidget::MusicInfoItemWidget( PlayerListWidget *parent ) : QWidget( parent ), MusicInfoItem( parent ) {
	index = 0;
	splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	// 开启鼠标穿透
	setAttribute( Qt::WA_TransparentForMouseEvents, true );
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
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( indexWidth, currentHeight ) );
	painter.drawText( drawRect, formatStringIndex );
	drawOffsetX += indexWidth + offsetSplitX;

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
