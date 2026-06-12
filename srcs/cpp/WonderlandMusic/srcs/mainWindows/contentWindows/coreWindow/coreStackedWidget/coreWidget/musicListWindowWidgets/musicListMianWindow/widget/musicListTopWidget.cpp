#include "musicListTopWidget.h"

#include <QLabel>
#include <QPainter>

#include <render/render.h>

void MusicListTopWidget::initItemSize( const FontRender &font_render, int &result_width, int &result_height ) const {
	const StringFontSize *stringFontSize;
	stringFontSize = font_render.getTxtFontSize( );
	result_width = stringFontSize->getHorizontalAdvance( );
	result_height = stringFontSize->getHeight( );
}
MusicListTopWidget::MusicListTopWidget( QWidget *parent ) : BaseWidget( parent ) {
	musicNameItem = new FontRender( tr( "歌名" ) );
	musicSingerItem = new FontRender( tr( "歌手" ) );
	musicPlayerTimeItem = new FontRender( tr( "时长" ) );
	decollatorWidth = 2;
	decollatorInterspace = 10;
	int compHeight;
	initItemSize( *musicNameItem, musicNameItemWidth, currentWidgetHeight );
	currentWidgetWidget = musicNameItemWidth + decollatorInterspace; // 增加前方空间
	initItemSize( *musicSingerItem, musicSingerItemWidth, compHeight );
	currentWidgetWidget += musicSingerItemWidth + decollatorInterspace; // 增加前方空间
	if( compHeight > currentWidgetHeight )
		currentWidgetHeight = compHeight;
	initItemSize( *musicPlayerTimeItem, musicPlayerTimeItemWidth, compHeight );
	currentWidgetWidget += musicPlayerTimeItemWidth + decollatorInterspace; // 增加前方空间
	if( compHeight > currentWidgetHeight )
		currentWidgetHeight = compHeight;
	currentWidgetWidget += decollatorInterspace; // 增加末尾空间
	setFixedSize( currentWidgetWidget, currentWidgetHeight );
}
int MusicListTopWidget::getMusicNameItemWidth( ) const {
	return musicNameItemWidth;
}
int MusicListTopWidget::getMusicSingerItemWidth( ) const {
	return musicSingerItemWidth;
}
int MusicListTopWidget::getMusicPlayerTimeItemWidth( ) const {
	return musicPlayerTimeItemWidth;
}
void MusicListTopWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
}
void MusicListTopWidget::paintEvent( QPaintEvent *event ) {
	BaseWidget::paintEvent( event );
	QPainter painter;
	painter.begin( this );
	int decollatorHalf = ( decollatorInterspace - decollatorWidth ) / 2;
	drawOffsetX = decollatorHalf;

	auto pen = painter.pen( );
	pen.setWidth( decollatorWidth );

	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentWidgetHeight );

	drawOffsetX += decollatorHalf;
	drawPoint.setX( drawOffsetX );

	drawRenderBuff = musicNameItem->getRenderBuff( );
	painter.drawImage( drawPoint, *drawRenderBuff );
	drawOffsetX += musicNameItemWidth + decollatorHalf;
	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentWidgetHeight );

	drawOffsetX += decollatorHalf;
	drawPoint.setX( drawOffsetX );
	drawRenderBuff = musicSingerItem->getRenderBuff( );
	painter.drawImage( drawPoint, *drawRenderBuff );
	drawOffsetX += musicNameItemWidth + decollatorHalf;
	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentWidgetHeight );

	drawOffsetX += decollatorHalf;
	drawPoint.setX( drawOffsetX );
	drawRenderBuff = musicPlayerTimeItem->getRenderBuff( );
	painter.drawImage( drawPoint, *drawRenderBuff );
	drawOffsetX += musicSingerItemWidth + decollatorHalf;
	painter.drawLine( drawOffsetX, 0, drawOffsetX, currentWidgetHeight );

	painter.end( );
}
