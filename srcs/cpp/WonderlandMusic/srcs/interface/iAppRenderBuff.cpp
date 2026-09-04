#include "iAppRenderBuff.h"

#include <qimage.h>

IAppRenderBuff::IAppRenderBuff( ) {
	renderBuff = new QImage;
}

IAppRenderBuff::~IAppRenderBuff( ) {
	delete renderBuff;
}

QImage * IAppRenderBuff::getRenderBuff( ) const {
	return renderBuff;
}
