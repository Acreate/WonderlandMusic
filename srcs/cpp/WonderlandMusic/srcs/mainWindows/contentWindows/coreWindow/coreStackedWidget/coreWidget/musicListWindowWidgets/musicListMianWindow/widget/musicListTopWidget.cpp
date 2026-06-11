#include "musicListTopWidget.h"

#include <QLabel>
#include <QPainter>

MusicListTopWidget::MusicListTopWidget( QWidget *parent ) : BaseWidget( parent ) {
	musicNameItem = new QLabel( tr( "歌名" ), this );
	musicSingerItem = new QLabel( tr( "歌手" ), this );
	musicPlayerTimeItem = new QLabel( tr( "时长" ), this );
	musicNameItem->adjustSize( );
	int height = musicNameItem->height( );
	musicSingerItem->adjustSize( );
	int compHeight = musicSingerItem->height( );
	if( compHeight > height )
		height = compHeight;
	musicPlayerTimeItem->adjustSize( );
	compHeight = musicPlayerTimeItem->height( );
	if( compHeight > height )
		height = compHeight;
	setFixedHeight( height );
}
int MusicListTopWidget::getMusicNameItemWidth( ) const {
	return musicNameItem->width( );
}
int MusicListTopWidget::getMusicSingerItemWidth( ) const {
	return musicSingerItem->width( );
}
int MusicListTopWidget::getMusicPlayerTimeItemWidth( ) const {
	return musicPlayerTimeItem->width( );
}
void MusicListTopWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
	int offsetX;
	int sides = 5 * 2;
	offsetX = sides;
	musicNameItem->move( offsetX, 0 );
	offsetX += musicNameItem->width( ) + sides * 2;
	musicSingerItem->move( offsetX, 0 );
	offsetX += musicSingerItem->width( ) + sides;
	musicPlayerTimeItem->move( offsetX, 0 );
}
void MusicListTopWidget::paintEvent( QPaintEvent *event ) {
	BaseWidget::paintEvent( event );
}
