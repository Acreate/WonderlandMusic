#include "musicItemWidthInfo.h"

#include <QWidget>
#include <qfontmetrics.h>

#include "../application/appInstance/appDataManage/translate/musicTitleWidgetTranslate.h"
#include "../application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "../component/musicWindow/interface/widget/iMusicTitleWidget.h"

#include "../head/result_message_out.h"

#include "../tools/instanceTools.h"
MusicItemWidthInfo::MusicItemWidthInfo( ) {
	appendTypeInfo( this );
}
MusicItemWidthInfo::~MusicItemWidthInfo( ) {
}
MusicItemWidthInfo::MusicItemWidthInfo( const MusicItemWidthInfo &other ) : IMusicItemWidthInfo { other },
	suggestHeight { other.suggestHeight },
	clickWidth { other.clickWidth },
	intervalWidth { other.intervalWidth },
	separatorWidth { other.separatorWidth },
	musicCodeWidth { other.musicCodeWidth },
	musicNameWidth { other.musicNameWidth },
	musicSingerNameWidth { other.musicSingerNameWidth },
	musicDurationTimeWidth { other.musicDurationTimeWidth },
	minItemWidth { other.minItemWidth } {
}
MusicItemWidthInfo & MusicItemWidthInfo::operator=( const MusicItemWidthInfo &other ) {
	if( this == &other )
		return *this;
	IMusicItemWidthInfo::operator =( other );
	suggestHeight = other.suggestHeight;
	clickWidth = other.clickWidth;
	intervalWidth = other.intervalWidth;
	separatorWidth = other.separatorWidth;
	musicCodeWidth = other.musicCodeWidth;
	musicNameWidth = other.musicNameWidth;
	musicSingerNameWidth = other.musicSingerNameWidth;
	musicDurationTimeWidth = other.musicDurationTimeWidth;
	minItemWidth = other.minItemWidth;
	return *this;
}
void MusicItemWidthInfo::setSuggestHeight( const int suggest_height ) {
	suggestHeight = suggest_height;
}
void MusicItemWidthInfo::setClickWidth( const int click_width ) {
	clickWidth = click_width;
}
void MusicItemWidthInfo::setIntervalWidth( const int interval_width ) {
	intervalWidth = interval_width;
}
void MusicItemWidthInfo::setSeparatorWidth( const int separator_width ) {
	separatorWidth = separator_width;
}
void MusicItemWidthInfo::setMusicCodeWidth( const int music_code_width ) {
	musicCodeWidth = music_code_width;
}
void MusicItemWidthInfo::setMusicNameWidth( const int music_name_width ) {
	musicNameWidth = music_name_width;
}
void MusicItemWidthInfo::setMusicSingerNameWidth( const int music_singer_name_width ) {
	musicSingerNameWidth = music_singer_name_width;
}
void MusicItemWidthInfo::setMusicDurationTimeWidth( const int music_duration_time_width ) {
	musicDurationTimeWidth = music_duration_time_width;
}
void MusicItemWidthInfo::setMinItemWidth( const int min_item_width ) {
	minItemWidth = min_item_width;
}
bool MusicItemWidthInfo::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
int MusicItemWidthInfo::defaultHeight( ) const {
	int height = 0;
	AppRenderImage *appRenderImage = InstanceTools::getAppRenderImage( );
	const QFontMetrics *fontMetrics = nullptr;
	if( appRenderImage ) {
		fontMetrics = appRenderImage->getFontMetrics( );
		if( fontMetrics )
			height = fontMetrics->height( );
	}
	if( fontMetrics == nullptr )
		return QFontMetrics( QFont( ) ).height( );
	return height;
}
int MusicItemWidthInfo::getSuggestHeight( ) const {
	return suggestHeight;
}
int MusicItemWidthInfo::getClickWidth( ) const {
	return clickWidth;
}
int MusicItemWidthInfo::getCalculateMinWidth( ) const {
	return clickWidth * 5 + musicCodeWidth + musicNameWidth + musicSingerNameWidth + musicDurationTimeWidth;
}
int MusicItemWidthInfo::getIntervalWidth( ) const {
	return intervalWidth;
}
int MusicItemWidthInfo::getSeparatorWidth( ) const {
	return separatorWidth;
}
int MusicItemWidthInfo::getMusicCodeWidth( ) const {
	return musicCodeWidth;
}
int MusicItemWidthInfo::getMusicNameWidth( ) const {
	return musicNameWidth;
}
int MusicItemWidthInfo::getMusicSingerNameWidth( ) const {
	return musicSingerNameWidth;
}
int MusicItemWidthInfo::getMusicDurationTimeWidth( ) const {
	return musicDurationTimeWidth;
}
int MusicItemWidthInfo::getMinItemWidth( ) const {
	return minItemWidth;
}
bool MusicItemWidthInfo::setIMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) {
	suggestHeight = music_item_width_info.getSuggestHeight( );
	clickWidth = music_item_width_info.getClickWidth( );
	intervalWidth = music_item_width_info.getIntervalWidth( );
	separatorWidth = music_item_width_info.getSeparatorWidth( );
	musicCodeWidth = music_item_width_info.getMusicCodeWidth( );
	musicNameWidth = music_item_width_info.getMusicNameWidth( );
	musicSingerNameWidth = music_item_width_info.getMusicSingerNameWidth( );
	musicDurationTimeWidth = music_item_width_info.getMusicDurationTimeWidth( );
	minItemWidth = music_item_width_info.getMinItemWidth( );
	return true;
}
bool MusicItemWidthInfo::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}
bool MusicItemWidthInfo::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
bool MusicItemWidthInfo::updateInfo( ) {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, getSuggestHeight, QObject::tr( "获取 AppRenderImage* 失败" ) );
	auto fontMetrics = appRenderImage->getFontMetrics( );
	if( fontMetrics == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appRenderImage, getFontMetrics, QObject::tr( "获取 QFontMetrics* 失败" ) );
	suggestHeight = fontMetrics->height( );
	if( AppTranslateTools::getMusicTitleWidget( [&fontMetrics, this] ( MusicTitleWidgetTranslate &translate ) {
		const QString &musicCode = translate.getMusicCode( );
		const QString &musicName = translate.getMusicName( );
		const QString &musicSingeName = translate.getMusicSingeName( );
		const QString &musicDurationTime = translate.getMusicDurationTime( );
		musicCodeWidth = fontMetrics->horizontalAdvance( musicCode );
		musicNameWidth = fontMetrics->horizontalAdvance( musicName );
		musicSingerNameWidth = fontMetrics->horizontalAdvance( musicSingeName );
		musicDurationTimeWidth = fontMetrics->horizontalAdvance( musicDurationTime );
		return true;
	} ) == false )
		return Result_Var_Messag_Ptr_Out_Args( false, appRenderImage, QObject::tr( "AppTranslateTools::getMusicTitleWidget 异常" ) );
	separatorWidth = 5;
	intervalWidth = 2;
	minItemWidth = intervalWidth * 2 + separatorWidth;
	clickWidth = intervalWidth * 2 + separatorWidth;
	return true;
}
int MusicItemWidthInfo::getCalculateHeight( ) const {
	if( musicTitleWidget == nullptr )
		return defaultHeight( );
	auto widget = musicTitleWidget->toWidget( );
	if( widget == nullptr )
		return defaultHeight( );
	return widget->height( );
}
IMusicTitleWidget * MusicItemWidthInfo::setMusicTitleWidget( IMusicTitleWidget *music_title_widget ) {
	this->musicTitleWidget = music_title_widget;
	return nullptr;
}
IMusicTitleWidget * MusicItemWidthInfo::getMusicTitleWidget( ) {
	return musicTitleWidget;
}
