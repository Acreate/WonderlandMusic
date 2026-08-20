#include "fontTools.h"

#include <qfontmetrics.h>

#include "instanceTools.h"

#include "../application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h"

bool FontTools::getFontHeight( int &result_height, const QFont &font ) {
	return getFontHeight( result_height, QFontMetrics( font ) );
}
bool FontTools::getFontHeight( int &result_height, const QFontMetrics &font_metrics ) {
	result_height = font_metrics.height( );
	return result_height;
}
bool FontTools::getFontHeight( int &result_height ) {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;
	const QFontMetrics *fontMetrics = appRenderImage->getFontMetrics( );
	if( fontMetrics == nullptr )
		return false;
	result_height = fontMetrics->height( );
	return result_height;
}
