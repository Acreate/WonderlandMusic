#include "musicListTopWidget.h"

#include <QLabel>
#include <QPainter>

#include <render/render.h>

#include "musicListItemWidget/playerListItem.h"

void MusicListTopWidget::initItemSize( const FontRender &font_render, int &result_width, int &result_height ) const {
	const StringFontSize *stringFontSize;
	stringFontSize = font_render.getTxtFontSize( );
	result_width = stringFontSize->getHorizontalAdvance( );
	result_height = stringFontSize->getHeight( );
}
MusicListTopWidget::MusicListTopWidget( QWidget *parent ) : BaseWidget( parent ) {

	playerListItem = new PlayerListItem;
	playerListItem->appendItem( tr( "歌名" ) );
	playerListItem->appendItem( tr( "歌手" ) );
	playerListItem->appendItem( tr( "时长" ) );
	drawBuff = new QImage( 1, 1, QImage::Format_RGBA8888 );
	playerListItem->renderBuff( drawBuff );
	setFixedSize( drawBuff->size( ) );
}
MusicListTopWidget::~MusicListTopWidget( ) {
	delete playerListItem;
	delete drawBuff;
}
void MusicListTopWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );

}
void MusicListTopWidget::paintEvent( QPaintEvent *event ) {
	BaseWidget::paintEvent( event );
	QPainter painter;
	painter.begin( this );
	painter.drawImage( 0, 0, *drawBuff );
	painter.end( );
}
