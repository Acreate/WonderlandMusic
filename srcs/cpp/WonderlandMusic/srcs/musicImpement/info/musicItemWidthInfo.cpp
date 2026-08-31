#include "musicItemWidthInfo.h"

#include <QJsonObject>
#include <qfontmetrics.h>

#include <application/appInstance/appDataManage/translate/musicTitleWidgetTranslate.h>
#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <component/musicWindow/interface/widget/iMusicTitleWidget.h>

#include <head/result_message_out.h>

#include <tools/instanceTools.h>

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>

#include "../../application/appInstance/appDataManage/jsonKey/appDataManageJsonKey.h"
#include "../../application/appInstance/appDataManage/jsonKey/musicItemWidthInfoJsonKey.h"
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
	if( AppJsonKeyTools::getMusicItemWidthInfo( [&get_json_object, this] ( const MusicItemWidthInfoJsonKey &json_key ) {
		get_json_object.insert( json_key.getClickWidth( ), clickWidth );
		get_json_object.insert( json_key.getIntervalWidth( ), intervalWidth );
		get_json_object.insert( json_key.getMinItemWidth( ), minItemWidth );
		get_json_object.insert( json_key.getMusicCodeWidth( ), musicCodeWidth );
		get_json_object.insert( json_key.getMusicDurationTimeWidth( ), musicDurationTimeWidth );
		get_json_object.insert( json_key.getMusicSingerNameWidth( ), musicSingerNameWidth );
		get_json_object.insert( json_key.getSeparatorWidth( ), separatorWidth );
		get_json_object.insert( json_key.getSuggestHeight( ), suggestHeight );
		return true;
	} ) == false )
		return false;

	return true;
}
bool MusicItemWidthInfo::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getMusicItemWidthInfo( [&set_json_object, this] ( const MusicItemWidthInfoJsonKey &json_key ) {
		#define find_over( _equ_var, _find_key, _conver_function, _find_result, _find_end, _json_object ) \
			_find_result = _json_object.find( _find_key ); \
			if( _find_result == _find_end ) \
				return false; \
			_equ_var = _find_result->_conver_function( _equ_var );

		QJsonObject::const_iterator find;
		auto end = set_json_object.end( );
		#define find_integer_over(  _equ_var, _find_key ) \
			find_over( _equ_var, _find_key, toInteger, find, end, set_json_object )

		find_integer_over( clickWidth, json_key.getClickWidth( ) )
		find_integer_over( intervalWidth, json_key.getIntervalWidth( ) )
		find_integer_over( intervalWidth, json_key.getIntervalWidth( ) )
		find_integer_over( minItemWidth, json_key.getMinItemWidth( ) )
		find_integer_over( musicCodeWidth, json_key.getMusicCodeWidth( ) )
		find_integer_over( musicDurationTimeWidth, json_key.getMusicDurationTimeWidth( ) )
		find_integer_over( musicSingerNameWidth, json_key.getMusicSingerNameWidth( ) )
		find_integer_over( separatorWidth, json_key.getSeparatorWidth( ) )
		find_integer_over( suggestHeight, json_key.getSuggestHeight( ) )

		return true;
	} ) == false )
		return false;

	return true;
}
bool MusicItemWidthInfo::initInfo( ) {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, getSuggestHeight, QObject::tr( "获取 AppRenderImage* 失败" ) );
	auto fontMetrics = appRenderImage->getFontMetrics( );
	if( fontMetrics == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, appRenderImage, getFontMetrics, QObject::tr( "获取 QFontMetrics* 失败" ) );
	if( AppTranslateTools::getMusicTitleWidget( [&fontMetrics, this] ( MusicTitleWidgetTranslate &translate ) {
		const QString &musicCode = translate.getMusicCode( );
		const QString &musicName = translate.getMusicName( );
		const QString &musicSingeName = translate.getMusicSingeName( );
		const QString &musicDurationTime = translate.getMusicDurationTime( );
		musicCodeWidth = fontMetrics->horizontalAdvance( musicCode );
		musicNameWidth = fontMetrics->horizontalAdvance( musicName );
		musicSingerNameWidth = fontMetrics->horizontalAdvance( musicSingeName );
		musicDurationTimeWidth = fontMetrics->horizontalAdvance( musicDurationTime );
		suggestHeight = fontMetrics->height( );
		return true;
	} ) == false )
		return Result_Var_Messag_Ptr_Out_Args( false, appRenderImage, QObject::tr( "AppTranslateTools::getMusicTitleWidget 异常" ) );
	separatorWidth = 5;
	intervalWidth = 2;
	minItemWidth = intervalWidth * 2 + separatorWidth;
	clickWidth = intervalWidth * 2 + separatorWidth;
	return true;
}
IMusicTitleWidget * MusicItemWidthInfo::setMusicTitleWidget( IMusicTitleWidget *music_title_widget ) {
	auto old = this->musicTitleWidget;
	this->musicTitleWidget = music_title_widget;
	return old;
}
IMusicTitleWidget * MusicItemWidthInfo::getMusicTitleWidget( ) {
	return musicTitleWidget;
}
bool MusicItemWidthInfo::synchronization( ) {
	if( musicCentreWidget == nullptr )
		return false;
	return musicCentreWidget->repaintListWidget( );
}
MusicCentreWidget * MusicItemWidthInfo::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicItemWidthInfo::isSuggestHeight( const int *width_var_ptr ) const {
	return width_var_ptr == &suggestHeight;
}
bool MusicItemWidthInfo::isClickWidth( const int *width_var_ptr ) const {
	return width_var_ptr == &clickWidth;
}

bool MusicItemWidthInfo::isIntervalWidth( const int *width_var_ptr ) const {
	return width_var_ptr == &intervalWidth;
}
bool MusicItemWidthInfo::isSeparatorWidth( const int *width_var_ptr ) const {
	return width_var_ptr == &separatorWidth;
}
bool MusicItemWidthInfo::isMusicCodeWidth( const int *width_var_ptr ) const {
	return width_var_ptr == &musicCodeWidth;
}
bool MusicItemWidthInfo::isMusicNameWidth( const int *width_var_ptr ) const {
	return width_var_ptr == &musicNameWidth;
}
bool MusicItemWidthInfo::isMusicSingerNameWidth( const int *width_var_ptr ) const {
	return width_var_ptr == &musicSingerNameWidth;
}
bool MusicItemWidthInfo::isMusicDurationTimeWidth( const int *width_var_ptr ) const {
	return width_var_ptr == &musicDurationTimeWidth;
}
bool MusicItemWidthInfo::getPosItemWidthPtr( const int *&result_width_var_ptr, int &result_index, const int x ) const {
	int leftX = minItemWidth;
	if( x < leftX ) {
		result_width_var_ptr = &minItemWidth;
		result_index = 0;
		return true;
	}
	leftX = leftX + musicCodeWidth;
	if( x < leftX ) {
		result_width_var_ptr = &musicCodeWidth;
		result_index = 1;
		return true;
	}
	leftX = leftX + minItemWidth + musicNameWidth;
	if( x < leftX ) {
		result_width_var_ptr = &musicNameWidth;
		result_index = 2;
		return true;
	}
	leftX = leftX + minItemWidth + musicSingerNameWidth;
	if( x < leftX ) {
		result_width_var_ptr = &musicSingerNameWidth;
		result_index = 3;
		return true;
	}
	leftX = leftX + minItemWidth + musicDurationTimeWidth;
	if( x < leftX ) {
		result_width_var_ptr = &musicDurationTimeWidth;
		result_index = 4;
		return true;
	}
	return false;
}
