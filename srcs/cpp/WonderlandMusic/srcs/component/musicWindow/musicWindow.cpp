#include "musicWindow.h"

#include <QJsonObject>

#include "../../application/appInstance/appDataManage/jsonKey/musicWindowJsonKey.h"
#include "../../application/appInstance/appDataManage/translate/musicWindowTranslate.h"

#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../mutex/userMutex.h"
#include "../../tools/pathTools.h"

#include "interface/widget/iMusicCentreWidget.h"

MusicWindow::MusicWindow( ) {
}
MusicWindow::~MusicWindow( ) {
	deleteResource( );
}
bool MusicWindow::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	takeCentralWidget( );
	musicCentreWidget = nullptr;
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
bool MusicWindow::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	return true;
}
bool MusicWindow::init( ) {
	if( AppTranslateTools::getMusicWindow( [this] ( MusicWindowTranslate &translate ) {
		auto &titleName = translate.getTitleName( );
		setName( titleName );
		return true;
	} ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, init, tr( "无法获取翻译实例" ) );
	return true;
}
bool MusicWindow::initAfter( ) {
	return true;
}
bool MusicWindow::getJsonData( QJsonObject &get_json_object ) const {
	if( AppJsonKeyTools::getMusicWindow( [this, &get_json_object] ( const MusicWindowJsonKey &json_key ) {
		QJsonObject musicCenreJsonObject;
		if( musicCentreWidget->getJsonData( musicCenreJsonObject ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicCentreWidget, getJsonData, tr( "配置 json 数据异常" ) );
		get_json_object.insert( json_key.getMusicCentreWidgetKey( ), musicCenreJsonObject );
		return true;
	} ) == false )
		return false;
	return true;
}
bool MusicWindow::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getMusicWindow( [&set_json_object, this] ( const MusicWindowJsonKey &json_key ) {
		const auto &musicCentreWidgetKey = json_key.getMusicCentreWidgetKey( );
		auto iterator = set_json_object.begin( );
		auto end = set_json_object.end( );
		for( ; iterator != end; ++iterator ) {
			auto key = iterator.key( );
			if( key == musicCentreWidgetKey ) {
				auto jsonObject = iterator.value( ).toObject( );
				if( musicCentreWidget->setJsonData( jsonObject ) == false )
					return Result_Var_Function_Messag_Ptr_Out_Args( false, musicCentreWidget, setJsonData, tr( "获取 json 数据异常" ) );
			}
		}

		return true;
	} ) == false )
		return false;
	return true;
}
QString MusicWindow::getTypeName( ) const {
	return metaObject( )->className( );
}
IMusicFavoriteWidget * MusicWindow::getMusicFavoriteWidget( ) const {
	return musicCentreWidget->getMusicFavoriteWidget( );
}
IMusicListWidget * MusicWindow::getMusicListWidget( ) const {
	return musicCentreWidget->getMusicListWidget( );
}
IMusicTitleWidget * MusicWindow::getMusicTitleWidget( ) const {
	return musicCentreWidget->getMusicTitleWidget( );
}
IMusicFavoriteMenu * MusicWindow::getMusicFavoriteMenu( ) const {
	return musicCentreWidget->getMusicFavoriteMenu( );
}
IMusicListMenu * MusicWindow::getMusicListMenu( ) const {
	return musicCentreWidget->getMusicListMenu( );
}
IMusicWidgetSizeInfo * MusicWindow::getMusicWidgetSizeInfo( ) const {
	return musicCentreWidget->getMusicWidgetSizeInfo( );
}
IMusicFavoriteWidget * MusicWindow::setMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) {
	return musicCentreWidget->setMusicFavoriteWidget( music_favorite_widget );
}
IMusicListWidget * MusicWindow::setMusicListWidget( IMusicListWidget *const music_list_widget ) {
	return musicCentreWidget->setMusicListWidget( music_list_widget );
}
IMusicTitleWidget * MusicWindow::setMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) {
	return musicCentreWidget->setMusicTitleWidget( music_title_widget );
}
IMusicDataManage * MusicWindow::setMusicDataManage( IMusicDataManage *const music_data_manage ) {
	return musicCentreWidget->setMusicDataManage( music_data_manage );
}
IMusicDataManage * MusicWindow::getMusicDataManage( ) const {
	return musicCentreWidget->getMusicDataManage( );
}
bool MusicWindow::repaintListWidget( ) {
	if( musicCentreWidget == nullptr )
		return false;
	return musicCentreWidget->repaintListWidget( );
}
bool MusicWindow::repaintTitleWidget( ) {
	if( musicCentreWidget == nullptr )
		return false;
	return musicCentreWidget->repaintTitleWidget( );
}
bool MusicWindow::repaintFavoriteWidget( ) {
	if( musicCentreWidget == nullptr )
		return false;
	return musicCentreWidget->repaintFavoriteWidget( );
}
bool MusicWindow::repaintMusicCentreWidget( ) {
	if( musicCentreWidget == nullptr )
		return false;
	return musicCentreWidget->repaintMusicCentreWidget( );
}
bool MusicWindow::repaintChildrenWidget( ) {
	if( repaintTitleWidget( ) == false )
		return false;
	if( repaintFavoriteWidget( ) == false )
		return false;
	if( repaintListWidget( ) == false )
		return false;
	return true;
}
bool MusicWindow::synchronizationChildrenWidgetSize( ) {
	if( musicCentreWidget == nullptr )
		return false;
	return musicCentreWidget->synchronizationChildrenWidgetSize( );
}
IMusicCentreWidget * MusicWindow::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	if( music_centre_widget == nullptr ) {
		auto old = music_centre_widget;
		takeCentralWidget( );
		musicCentreWidget = nullptr;
		return old;
	}
	auto widget = music_centre_widget->toWidget( );
	if( widget == nullptr )
		return music_centre_widget;
	if( music_centre_widget->setMusicWindow( this ) == false )
		return music_centre_widget;
	if( music_centre_widget->repaintMusicCentreWidget( ) == false )
		return music_centre_widget;
	if( music_centre_widget->synchronizationChildrenWidgetSize( ) == false )
		return music_centre_widget;
	auto old = musicCentreWidget;
	musicCentreWidget = music_centre_widget;
	takeCentralWidget( );
	setCentralWidget( widget );
	return old;
}
QWidget * MusicWindow::toWidget( ) {
	return this;
}

IMusicCentreWidget * MusicWindow::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicWindow::showPanelBefore( ) {
	return true;
}
bool MusicWindow::hidePanelBefore( ) {
	return true;
}
bool MusicWindow::releasePanelBefore( ) {
	if( AppJsonKeyTools::getMusicWindow( [this] ( const MusicWindowJsonKey &json_key ) {
		QJsonObject jsonObject;
		if( getJsonData( jsonObject ) == false )
			return false;
		if( PathTools::writeJsonObject( jsonObject, json_key.getFilePath( ) ) == false )
			return false;
		return true;
	} ) == false )
		return false;
	return true;
}
