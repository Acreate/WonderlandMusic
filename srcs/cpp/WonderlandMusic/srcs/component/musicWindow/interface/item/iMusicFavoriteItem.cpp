#include "iMusicFavoriteItem.h"

#include "iMusicItem.h"

#include "../../../../head/result_message_out.h"

#include "../ItemWidget/iMusicFavoriteItemWidget.h"
IMusicFavoriteItem::IMusicFavoriteItem( ) {
	appendTypeInfo( this );
}
bool IMusicFavoriteItem::setMusicFavoriteItemWidgetBindMusicFavoriteItem( ) {
	auto musicFavoriteItemWidget = getMusicFavoriteItemWidget( );
	if( musicFavoriteItemWidget == nullptr )
		return false;
	return musicFavoriteItemWidget->setBindMusicFavoriteItem( this );
}
bool IMusicFavoriteItem::setMusicFavoriteItemWidgetMusicCentreWidget( ) {
	auto widget = getMusicFavoriteItemWidget( );
	if( widget == nullptr )
		return false;
	auto musicCentreWidget = getMusicCentreWidget( );
	return widget->setMusicCentreWidget( musicCentreWidget );
}
bool IMusicFavoriteItem::setMusicItemMusicCentreWidget( ) {
	std::vector< IMusicItem * > result;
	size_t size = getMusicVectorClone( result );
	if( size == 0 )
		return true;
	auto musicCentreWidget = getMusicCentreWidget( );
	auto data = result.data( );
	size_t index = 0;
	for( ; index < size; index += 1 )
		if( data[ index ]->setMusicCentreWidget( musicCentreWidget ) ) {
			Result_Var_Function_Messag_Ptr_Out_Args( false, data[ index ], setMusicCentreWidget, QObject::tr( "组件配置 MusicCentreWidget * 失败" ) );
		}
	return true;
}
