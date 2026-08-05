#include "musicCentreWidgetInfo.h"
bool MusicCentreWidgetInfo::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicCentreWidgetInfo::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicCentreWidgetInfo::readJsonData( ) {
	return true;
}
bool MusicCentreWidgetInfo::writeJsonData( ) {
	return true;
}
int MusicCentreWidgetInfo::getFavoriteWidgetWidth( ) const {
	return favoriteWidgetWidth;
}
int MusicCentreWidgetInfo::getToolWidgetWidth( ) const {
	return toolWidgetWidth;
}
int MusicCentreWidgetInfo::getTitleWidgetWidth( ) const {
	return titleWidgetWidth;
}
