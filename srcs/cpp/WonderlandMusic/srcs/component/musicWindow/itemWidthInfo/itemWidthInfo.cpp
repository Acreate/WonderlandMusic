#include "ItemWidthInfo.h"

#include <QJsonObject>

#include "../../../head/q_json_object.h"
ItemWidthInfo::ItemWidthInfo( ) {
}
ItemWidthInfo::ItemWidthInfo( int suggest_height, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width, int min_item_width ) : suggestHeight( suggest_height ),
	intervalWidth( interval_width ),
	separatorWidth( separator_width ),
	musicCodeWidth( music_code_width ),
	musicNameWidth( music_name_width ),
	musicSingerNameWidth( music_singer_name_width ),
	musicDurationTimeWidth( music_duration_time_width ),
	minItemWidth( min_item_width ) {
}
ItemWidthInfo::~ItemWidthInfo( ) {
}
int ItemWidthInfo::getSuggestHeight( ) const {
	return suggestHeight;
}
int ItemWidthInfo::getClickWidth( ) const {
	return clickWidth;
}
int ItemWidthInfo::getIntervalWidth( ) const {
	return intervalWidth;
}
int ItemWidthInfo::getSeparatorWidth( ) const {
	return separatorWidth;
}
int ItemWidthInfo::getMusicCodeWidth( ) const {
	return musicCodeWidth;
}
int ItemWidthInfo::getMusicNameWidth( ) const {
	return musicNameWidth;
}
int ItemWidthInfo::getMusicSingerNameWidth( ) const {
	return musicSingerNameWidth;
}
int ItemWidthInfo::getMusicDurationTimeWidth( ) const {
	return musicDurationTimeWidth;
}
int ItemWidthInfo::getMinItemWidth( ) const {
	return minItemWidth;
}
int ItemWidthInfo::getCalculateMinWidth( ) const {
	return clickWidth * 5 + musicCodeWidth + musicNameWidth + musicSingerNameWidth + musicDurationTimeWidth;
}
void ItemWidthInfo::getItemWidthInfo( int &result_interval_width, int &result_separator_width, int &result_music_code_width, int &result_music_name_width, int &result_music_singer_name_width, int &result_music_duration_time_width ) const {
}
void ItemWidthInfo::setItemWidthInfo( int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width ) {
}
bool ItemWidthInfo::getJsonData( QJsonObject &get_json_object ) const {
	instaerJsonObj( get_json_object, musicCodeWidth );
	instaerJsonObj( get_json_object, musicNameWidth );
	instaerJsonObj( get_json_object, musicSingerNameWidth );
	instaerJsonObj( get_json_object, musicDurationTimeWidth );
	return true;
}
bool ItemWidthInfo::setJsonData( const QJsonObject &set_json_object ) {
	QJsonObject::const_iterator end;
	QJsonObject::const_iterator find;
	bool ok;
	QString string;
	end = set_json_object.end( );

	conver_string_find_var( set_json_object, musicCodeWidth, find, end, ok, toInt );
	if( ok == false )
		return false;
	conver_string_find_var( set_json_object, musicNameWidth, find, end, ok, toInt );
	if( ok == false )
		return false;
	conver_string_find_var( set_json_object, musicSingerNameWidth, find, end, ok, toInt );

	if( ok == false )
		return false;
	conver_string_find_var( set_json_object, musicDurationTimeWidth, find, end, ok, toInt );

	if( ok == false )
		return false;
	return true;
}
