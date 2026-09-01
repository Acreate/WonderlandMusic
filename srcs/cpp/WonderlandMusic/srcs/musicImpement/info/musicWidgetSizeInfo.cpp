#include "musicWidgetSizeInfo.h"

#include <QJsonObject>
#include <qfontmetrics.h>

#include <application/appInstance/applicationManage.h>
#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <tools/instanceTools.h>

#include "../../application/appInstance/appDataManage/jsonKey/musicWidgetSizeInfoJsonKey.h"

#include "../../head/result_message_out.h"
MusicWidgetSizeInfo::MusicWidgetSizeInfo( ) {
	appendTypeInfo( this );
}
MusicWidgetSizeInfo::~MusicWidgetSizeInfo( ) {
}
bool MusicWidgetSizeInfo::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicWidgetSizeInfo::initInfo( ) {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;

	auto fontMetrics = appRenderImage->getFontMetrics( );
	if( fontMetrics == nullptr )
		return false;
	QString defaultWidth = QObject::tr( "默认" );
	favoriteWidth = fontMetrics->horizontalAdvance( defaultWidth );
	titleHeight = fontMetrics->height( );
	return true;
}

int MusicWidgetSizeInfo::getFavoriteWidth( ) const {
	return favoriteWidth;
}
int MusicWidgetSizeInfo::getTitleHeight( ) const {
	return titleHeight;
}
bool MusicWidgetSizeInfo::updateMusicWidgetLayout( ) {
	return false;
}
bool MusicWidgetSizeInfo::getJsonData( QJsonObject &get_json_object ) const {
	if( AppJsonKeyTools::getMusicWidgetSizeInfo( [&get_json_object, this] ( const MusicWidgetSizeInfoJsonKey &json_key ) {
		get_json_object.insert( json_key.getFavoriteWidth( ), favoriteWidth );
		get_json_object.insert( json_key.getTitleHeight( ), titleHeight );
		return true;
	} ) == false )
		return false;
	return true;
}
bool MusicWidgetSizeInfo::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getMusicWidgetSizeInfo( [&set_json_object, this] ( const MusicWidgetSizeInfoJsonKey &json_key ) {
		auto end = set_json_object.end( );
		auto find = set_json_object.find( json_key.getFavoriteWidth( ) );
		if( end == find )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, &set_json_object, find, QObject::tr("无法匹配 [%1]").arg( json_key.getFavoriteWidth( )) );
		favoriteWidth = find->toInteger( favoriteWidth );
		find = set_json_object.find( json_key.getTitleHeight( ) );
		if( end == find )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, &set_json_object, find, QObject::tr("无法匹配 [%1]").arg( json_key.getTitleHeight( )) );
		titleHeight = find->toInteger( titleHeight );
		return true;
	} ) == false )
		return false;
	return true;
}
IMusicCentreWidget * MusicWidgetSizeInfo::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
int MusicWidgetSizeInfo::setFavoriteWidth( const int &favoriet_width ) {
	int old = favoriet_width;
	favoriteWidth = old;
	return old;
}
int MusicWidgetSizeInfo::setTitleHeight( const int &title_height ) {
	int old = titleHeight;
	titleHeight = title_height;
	return old;
}
