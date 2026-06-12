#include "render.h"

#include <QImage>
#include <QPainter>
#include <qfontmetrics.h>
#include <qstring.h>

#include "../applications/applicationInstance.h"
FontRender::FontRender( ) : FontRender( "" ) { }
FontRender::FontRender( const QString &txt ) : txt( new QString( ) ), fontSize( new StringFontSize( ) ), renderBuff( new QImage( 1, 1, QImage::Format_RGBA8888 ) ) {
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
	renderBuff->fill( 0 );
	*renderBuff = renderBuff->scaled( fontSize->getHorizontalAdvance( ), fontSize->getHeight( ) );
	QPainter painter;
	painter.begin( renderBuff );
	painter.setFont( font );
	painter.drawText( 0, fontSize->getAscent( ), txt );
	painter.end( );
}
const QImage * const FontRender::getRenderBuff( ) const {
	if( stringLength == 0 )
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
	delete renderBuff;
	delete txt;

}
