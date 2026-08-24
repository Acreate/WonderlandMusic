#include "musicFavoriteWidget.h"

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>

#include "../../component/musicWindow/interface/info/iMusicDataManage.h"
#include "../../component/musicWindow/interface/item/iMusicFavoriteItem.h"

MusicFavoriteWidget::MusicFavoriteWidget( ) {
	appendTypeInfo( this );
}
MusicFavoriteWidget::~MusicFavoriteWidget( ) {
	deleteResource( );
}
bool MusicFavoriteWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicFavoriteWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicFavoriteWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
QWidget * MusicFavoriteWidget::toWidget( ) {
	return this;
}
MusicCentreWidget * MusicFavoriteWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicFavoriteWidget::deleteResource( ) {
	auto musicCentreWidget = getMusicCentreWidget( );
	if( musicCentreWidget )
		musicCentreWidget->removeMusicFavoriteWidget( this );
	return true;
}
bool MusicFavoriteWidget::initBefore( ) {
	return true;
}
bool MusicFavoriteWidget::init( ) {
	return true;
}
bool MusicFavoriteWidget::initAfter( ) {
	return true;
}
bool MusicFavoriteWidget::fromYPosGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &pos_y ) const {
	return true;
}
bool MusicFavoriteWidget::fromIndexGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &index ) const {
	return true;
}
bool MusicFavoriteWidget::fromNameGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const QString &index ) const {
	return true;
}
bool MusicFavoriteWidget::autoLayout( ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicDataManage = musicCentreWidget->getMusicDataManage( );
	if( musicDataManage == nullptr )
		return false;
	IMusicFavoriteItem *defaultItem;
	std::vector< IMusicFavoriteItem * > musicFavoriteItems;
	if( musicDataManage->getMusicFavoriteItem( defaultItem, musicFavoriteItems ) == false )
		return false;
	auto musicFavoriteItemWidget = defaultItem->getMusicFavoriteItemWidget(  );
	
	return true;
}
