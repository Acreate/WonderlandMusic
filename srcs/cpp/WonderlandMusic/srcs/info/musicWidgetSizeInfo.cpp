#include "musicWidgetSizeInfo.h"

#include <qfontmetrics.h>

#include "../application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "../tools/instanceTools.h"
MusicWidgetSizeInfo::MusicWidgetSizeInfo( ) {
	appendTypeInfo( this );
}
MusicWidgetSizeInfo::~MusicWidgetSizeInfo( ) {
}
bool MusicWidgetSizeInfo::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return false;
}
int MusicWidgetSizeInfo::getFavoriteWidth( ) const {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	auto fontMetrics = appRenderImage->getFontMetrics( );
	int horizontalAdvance = fontMetrics->horizontalAdvance( QObject::tr( "默认" ) );
	return horizontalAdvance;
}
int MusicWidgetSizeInfo::getTitleHeight( ) const {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	auto fontMetrics = appRenderImage->getFontMetrics( );
	return fontMetrics->height( );
}
bool MusicWidgetSizeInfo::updateMusicWidgetLayout( ) {
	return false;
}
bool MusicWidgetSizeInfo::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}
bool MusicWidgetSizeInfo::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
MusicCentreWidget * MusicWidgetSizeInfo::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
int MusicWidgetSizeInfo::setFavoriteWidth( const int &favoriet_width ) {
	return 0;
}
int MusicWidgetSizeInfo::setTitleHeight( const int &favoriet_width ) {
	return 0;
}
