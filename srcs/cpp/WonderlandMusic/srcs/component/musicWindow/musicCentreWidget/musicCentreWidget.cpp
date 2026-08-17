#include "musicCentreWidget.h"

#include <QJsonObject>
#include <QScrollArea>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/init_macro.h>
#include <head/release_macro.h>

#include <mutex/userMutex.h>

#include "../musicWindow.h"

#include "../../../head/result_message_out.h"

#include "../interface/menu/iMusicFavoriteMenu.h"
#include "../interface/menu/iMusicListMenu.h"
#include "../interface/widget/iMusicFavoriteWidget.h"
#include "../interface/widget/iMusicListWidget.h"
#include "../interface/widget/iMusicTitleWidget.h"

#include "../tools/MusicFavoriteWidgetTools.h"
#include "../tools/musicListWidgetTools.h"

#include "../transparencyScrollBar/transparencyScrollBar.h"

MusicCentreWidget::MusicCentreWidget( MusicWindow *parent ) : QWidget( parent ), musicWindow( parent ) {
}
MusicCentreWidget::~MusicCentreWidget( ) {
	deleteResource( );
}
bool MusicCentreWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	musicfavoriteWidgetScrollArea->takeWidget( );
	Delete_Resource_App_Core_Ptr( musicfavoriteWidgetScrollArea );
	musicListWidgetScrollArea->takeWidget( );
	Delete_Resource_App_Core_Ptr( musicListWidgetScrollArea );
	musicTitleWidgetScrollArea->takeWidget( );
	Delete_Resource_App_Core_Ptr( musicTitleWidgetScrollArea );

	Delete_Resource_App_Core_Ptr( musicFavoriteWidget );
	Delete_Resource_App_Core_Ptr( musicTitleWidget );
	Delete_Resource_App_Core_Ptr( musicListWidget );
	Delete_Resource_App_Core_Ptr( musicListMenu );
	Delete_Resource_App_Core_Ptr( musicFavoriteMenu );

	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}

void MusicCentreWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );

	calculateSize( );
}
QScrollArea * MusicCentreWidget::createControlScrollArea( ) {
	auto scrollArea = new QScrollArea( this );
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	return scrollArea;
}

bool MusicCentreWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	return true;
}
bool MusicCentreWidget::init( ) {
	return true;
}
bool MusicCentreWidget::initAfter( ) {
	musicfavoriteWidgetScrollArea = createControlScrollArea( );

	musicTitleWidgetScrollArea = createControlScrollArea( );
	musicListWidgetScrollArea = createControlScrollArea( );

	musicTitleWidgetScrollArea->setVerticalScrollBar( new TransparencyScrollBar( this ) );
	musicTitleWidgetScrollArea->setMouseTracking( true );
	musicTitleWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	auto verticalScrollBar = musicTitleWidgetScrollArea->verticalScrollBar( );
	if( verticalScrollBar )
		verticalScrollBar->setEnabled( false );
	auto horizontalScrollBar = musicTitleWidgetScrollArea->horizontalScrollBar( );
	auto scrollBar = musicListWidgetScrollArea->horizontalScrollBar( );

	connect( scrollBar, &QScrollBar::valueChanged, horizontalScrollBar, &QScrollBar::setValue );
	connect( scrollBar, &QScrollBar::rangeChanged, horizontalScrollBar, &QScrollBar::setRange );

	calculateSize( );

	musicListWidgetScrollArea->show( );
	musicfavoriteWidgetScrollArea->show( );
	musicTitleWidgetScrollArea->show( );
	return true;
}

bool MusicCentreWidget::calculateSize( ) {
	if( userMutex == nullptr )
		return false;
	// 当前组件高度
	int thisCentreHeight = this->height( );
	if( thisCentreHeight <= 0 )
		return false;
	// 当前组件宽度
	int thisCentreWidthWidth = this->width( );
	if( thisCentreWidthWidth <= 0 )
		return false;
	// 组件建议宽度
	auto verticalScrollBar = musicfavoriteWidgetScrollArea->verticalScrollBar( );
	int modWidth = verticalScrollBar->width( );
	int suggestWidth = musicFavoriteWidget->toWidget( )->width( ) + modWidth;
	// 收藏组件的高度
	musicfavoriteWidgetScrollArea->setGeometry( 0, 0, suggestWidth, thisCentreHeight );
	musicfavoriteWidgetScrollArea->move( 0, 0 );

	// 剩余宽度
	modWidth = thisCentreWidthWidth - suggestWidth;
	// 建议高度
	int suggestHeight = musicTitleWidget->toWidget( )->height( );
	// 标题宽度
	musicTitleWidgetScrollArea->setGeometry( suggestWidth, 0, modWidth, suggestHeight );

	// 中心面板
	musicListWidgetScrollArea->setGeometry( suggestWidth, suggestHeight, modWidth, modHeight );

	return true;
}
bool MusicCentreWidget::getJsonData( QJsonObject &get_json_object ) const {
	QJsonObject musicTitleJson;
	if( musicTitleWidget->getJsonData( musicTitleJson ) == false )
		return false;
	QJsonObject musicFavoriteJson;
	if( musicFavoriteWidget->getJsonData( musicFavoriteJson ) == false )
		return false;
	QJsonObject musicListJson;
	if( musicListWidget->getJsonData( musicListJson ) == false )
		return false;
	get_json_object.insert( musicTitleWidget->getTypeName( ), musicTitleJson );
	get_json_object.insert( musicListWidget->getTypeName( ), musicListJson );
	get_json_object.insert( musicFavoriteWidget->getTypeName( ), musicFavoriteJson );
	return true;
}
bool MusicCentreWidget::setJsonData( const QJsonObject &set_json_object ) {
	auto end = set_json_object.end( );
	auto iterator = set_json_object.find( musicTitleWidget->getTypeName( ) );
	if( iterator == end )
		return false;
	QJsonObject musicTitleJson = iterator->toObject( );
	iterator = set_json_object.find( musicListWidget->getTypeName( ) );
	if( iterator == end )
		return false;
	QJsonObject musicListJson = iterator->toObject( );
	iterator = set_json_object.find( musicFavoriteWidget->getTypeName( ) );
	if( iterator == end )
		return false;
	QJsonObject musicFavoriteJson = iterator->toObject( );
	if( musicTitleWidget->setJsonData( musicTitleJson ) == false )
		return false;
	if( musicFavoriteWidget->setJsonData( musicFavoriteJson ) == false )
		return false;
	if( musicListWidget->setJsonData( musicListJson ) == false )
		return false;
	return true;
}

MusicWindow * MusicCentreWidget::getMusicWindow( ) const {
	return musicWindow;
}
IMusicFavoriteWidget * MusicCentreWidget::getMusicFavoriteWidget( ) const {
	return musicFavoriteWidget;
}

IMusicListWidget * MusicCentreWidget::getMusicListWidget( ) const {
	return musicListWidget;
}

IMusicTitleWidget * MusicCentreWidget::getMusicTitleWidget( ) const {
	return musicTitleWidget;
}
IMusicFavoriteMenu * MusicCentreWidget::getMusicFavoriteMenu( ) const {
	return musicFavoriteMenu;
}
IMusicListMenu * MusicCentreWidget::getMusicListMenu( ) const {
	return musicListMenu;
}
IMusicFavoriteWidget * MusicCentreWidget::setMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) {
	if( music_favorite_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_favorite_widget, music_favorite_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicFavoriteWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_favorite_widget, musicFavoriteWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	auto oldMenu = this->musicFavoriteWidget;
	this->musicFavoriteWidget = music_favorite_widget;
	return oldMenu;
}
IMusicListWidget * MusicCentreWidget::setMusicListWidget( IMusicListWidget *const music_list_widget ) {
	if( music_list_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_list_widget, music_list_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicListWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_list_widget, musicListWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	auto oldMenu = this->musicListWidget;
	this->musicListWidget = music_list_widget;
	return oldMenu;
}
IMusicTitleWidget * MusicCentreWidget::setMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) {
	if( music_title_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_title_widget, music_title_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicTitleWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_title_widget, musicTitleWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	auto oldMenu = this->musicTitleWidget;
	this->musicTitleWidget = music_title_widget;
	return oldMenu;
}

IMusicFavoriteMenu * MusicCentreWidget::setMusicFavoriteMenu( IMusicFavoriteMenu *music_favorite_menu ) {
	if( music_favorite_menu->setMusicCentreWidget( this ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_favorite_menu, music_favorite_menu, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicFavoriteMenu->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_favorite_menu, musicFavoriteMenu, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	auto oldMenu = this->musicFavoriteMenu;
	this->musicFavoriteMenu = music_favorite_menu;
	return oldMenu;
}
IMusicListMenu * MusicCentreWidget::setMusicListMenu( IMusicListMenu *music_list_menu ) {
	if( music_list_menu->setMusicCentreWidget( this ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_list_menu, music_list_menu, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( this->musicListMenu->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Messag_Ptr_Out_Args( music_list_menu, musicListMenu, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	auto oldMenu = this->musicListMenu;
	this->musicListMenu = music_list_menu;;
	return oldMenu;
}
