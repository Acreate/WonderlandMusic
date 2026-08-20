#include "iAppRenderBuff.h"

#include <qimage.h>

IAppRenderBuff::IAppRenderBuff( ) {
	renderBuff = new QImage;
}

IAppRenderBuff::~IAppRenderBuff( ) {
	delete renderBuff;
}

const QImage * IAppRenderBuff::getRenderBuff( ) const {
	return renderBuff;
}
