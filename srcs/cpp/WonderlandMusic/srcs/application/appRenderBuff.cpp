#include "appRenderBuff.h"

#include <qimage.h>

AppRenderBuff::AppRenderBuff( ) {
	renderBuff = new QImage( );
}

AppRenderBuff::~AppRenderBuff( ) {
	delete renderBuff;
}

const QImage * AppRenderBuff::getRenderBuff( ) const {
	return renderBuff;
}
