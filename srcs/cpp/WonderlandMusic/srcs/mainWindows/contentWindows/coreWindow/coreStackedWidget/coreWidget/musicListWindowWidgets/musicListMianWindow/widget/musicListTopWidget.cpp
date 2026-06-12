#include "musicListTopWidget.h"

#include <QLabel>
#include <QPainter>

#include <render/render.h>

void MusicListTopWidget::initItemSize( const FontRender &font_render, int &result_width, int &result_height ) const {
	const StringFontSize *stringFontSize;
	stringFontSize = font_render.getTxtFontSize( );
	result_width = stringFontSize->getHorizontalAdvance( );
	result_height = stringFontSize->getHorizontalAdvance( );
}
MusicListTopWidget::MusicListTopWidget( QWidget *parent ) : BaseWidget( parent ) {
	musicNameItem = new FontRender( tr( "歌名" ) );
	musicSingerItem = new FontRender( tr( "歌手" ) );
	musicPlayerTimeItem = new FontRender( tr( "时长" ) );

	int height;
	int compHeight;
	initItemSize( *musicNameItem, musicNameItemWidth, height );
	drawOffsetX = musicNameItemWidth;
	initItemSize( *musicSingerItem, musicSingerItemWidth, compHeight );
	drawOffsetX += musicSingerItemWidth;
	if( compHeight > height )
		height = compHeight;
	initItemSize( *musicPlayerTimeItem, musicPlayerTimeItemWidth, compHeight );
	drawOffsetX += musicPlayerTimeItemWidth;
	if( compHeight > height )
		height = compHeight;
	setFixedSize( drawOffsetX, height );
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
	drawOffsetX = 0;
	auto renderBuff = musicNameItem->getRenderBuff( );
	painter.drawImage( QPoint( drawOffsetX, 0 ), *renderBuff );
	drawOffsetX += musicNameItemWidth;
	renderBuff = musicSingerItem->getRenderBuff( );
	painter.drawImage( QPoint( drawOffsetX, 0 ), *renderBuff );
	drawOffsetX += musicSingerItemWidth;
	renderBuff = musicPlayerTimeItem->getRenderBuff( );
	painter.drawImage( QPoint( drawOffsetX, 0 ), *renderBuff );

	painter.end( );
}
