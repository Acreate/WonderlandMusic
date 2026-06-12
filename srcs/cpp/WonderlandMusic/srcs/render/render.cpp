#include "render.h"

#include <QImage>
#include <QPainter>
#include <qfontmetrics.h>
#include <qstring.h>

#include "../applications/applicationInstance.h"
FontRender::FontRender( ) : FontRender( "" ) { }
FontRender::FontRender( const QString &txt ) : FontRender( txt, true ) {
}
FontRender::FontRender( const QString &txt, bool is_render ) :
	isRender( is_render ), txt( new QString( ) ), fontSize( new StringFontSize( ) ), renderBuff( nullptr ) {
	setTxt( txt );
}
void FontRender::setTxt( const QString &txt ) {
	*this->txt = txt;
	stringLength = txt.length( );
	if( stringLength == 0 )
		return;
	auto render = ApplicationInstance::getApplicationInstance( )->getRender( );
	auto &&font = render->getFont( );
	QFontMetrics metrics( font );
	*fontSize = render->getTxtSize( metrics, txt );
	if( isRender == false )
		return;
	if( renderBuff == nullptr )
		renderBuff = new QImage( fontSize->getHorizontalAdvance( ), fontSize->getHeight( ), QImage::Format_RGBA8888 );
	else
		*renderBuff = QImage( fontSize->getHorizontalAdvance( ), fontSize->getHeight( ), QImage::Format_RGBA8888 );
	renderBuff->fill( 0 );
	QPainter painter;
	painter.begin( renderBuff );
	painter.setFont( font );
	painter.drawText( 0, fontSize->getAscent( ), txt );
	painter.end( );
}
const QImage * const FontRender::getRenderBuff( ) const {
	if( stringLength == 0 || isRender )
		return nullptr;
	return renderBuff;
}
const QString & FontRender::getTxt( ) const {
	return *txt;
}
const StringFontSize * const FontRender::getTxtFontSize( ) const {
	if( stringLength == 0 )
		return nullptr;
	return fontSize;
}
FontRender::~FontRender( ) {
	delete fontSize;
	if( renderBuff )
		delete renderBuff;
	delete txt;
}
bool FontRender::drawTarget( QPainter *painter_ptr, const int &x, const int &y ) {
	painter_ptr->drawText( x, fontSize->getAscent( ) + y, *txt );
	return true;
}
