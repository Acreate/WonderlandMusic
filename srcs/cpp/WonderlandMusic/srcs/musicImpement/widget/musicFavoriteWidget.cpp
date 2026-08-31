#include "musicFavoriteWidget.h"

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>

#include "../../component/musicWindow/interface/ItemWidget/iMusicFavoriteItemWidget.h"
#include "../../component/musicWindow/interface/info/iMusicDataManage.h"
#include "../../component/musicWindow/interface/item/iMusicFavoriteItem.h"

#include "../../head/result_message_out.h"

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
	int width, height;
	int offsetX, offsetY;
	if( musicDataManage->getMusicFavoriteItem( defaultItem, musicFavoriteItems ) == false )
		return false;
	auto musicFavoriteItemWidget = defaultItem->getMusicFavoriteItemWidget( );
	if( musicFavoriteItemWidget->setMusicFavoriteWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "默认项目配置收藏组件异常" ) );
	if( musicFavoriteItemWidget->setPos( 0, 0 ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "默认项目配置位置异常" ) );
	if( musicFavoriteItemWidget->updateLayout( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "默认项目配置更新布局异常" ) );
	if( musicFavoriteItemWidget->showItemWidget( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "默认项目配置显示异常" ) );
	if( musicFavoriteItemWidget->getSize( width, height ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "默认项目获取大小异常" ) );
	offsetX = width;
	offsetY = height;
	size_t count = musicFavoriteItems.size( );
	if( count ) {
		auto data = musicFavoriteItems.data( );
		size_t index = 0;
		for( ; index < count; index += 1 ) {
			musicFavoriteItemWidget = data[ index ]->getMusicFavoriteItemWidget( );
			if( musicFavoriteItemWidget->setMusicFavoriteWidget( this ) == false )
				return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "下标[%1]配置收藏组件异常" ).arg( index ) );
			if( musicFavoriteItemWidget->setPos( 0, 0 ) == false )
				return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "下标[%1]配置位置异常" ).arg( index ) );
			if( musicFavoriteItemWidget->updateLayout( ) == false )
				return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "下标[%1]配置更新布局异常" ).arg( index ) );
			if( musicFavoriteItemWidget->showItemWidget( ) == false )
				return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "下标[%1]配置显示异常" ).arg( index ) );
			if( musicFavoriteItemWidget->getSize( width, height ) == false )
				return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteItemWidget, setMusicFavoriteWidget, tr( "下标[%1]获取大小异常" ).arg( index ) );
			offsetY += height;
			if( offsetX < width )
				offsetX = width;
		}
	}
	resize( offsetX, offsetY );
	return true;
}
