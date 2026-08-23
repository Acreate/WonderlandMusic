#include "musicCentreWidget.h"

#include <QJsonObject>
#include <QScrollArea>

#include <application/appInstance/appDataManage.h>
#include <application/appInstance/appUserInterfaceManage/appMenuManage.h>

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/release_macro.h>
#include <head/result_message_out.h>

#include <info/musicWidgetSizeInfo.h>

#include <mutex/userMutex.h>

#include "../musicWindow.h"

#include <tools/instanceTools.h>

#include "../interface/info/iMusicItemWidthInfo.h"
#include "../interface/info/iMusicWidgetSizeInfo.h"
#include "../interface/widget/iMusicFavoriteWidget.h"
#include "../interface/widget/iMusicListWidget.h"
#include "../interface/widget/iMusicTitleWidget.h"

#include "../transparencyScrollBar/transparencyScrollBar.h"

MusicCentreWidget::MusicCentreWidget( MusicWindow *parent ) : QWidget( parent ), musicWindow( parent ) {
	appendTypeInfo( this );
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
	auto musicWidgetSizeInfo = getMusicWidgetSizeInfo( );
	if( musicWidgetSizeInfo == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, getMusicWidgetSizeInfo, tr( "找不到窗口大小组件" ) );
	if( userMutex == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, userMutex, tr( "锁未能确定指向有效对象" ) );
	userMutex->lock( );
	// 当前组件高度
	int thisCentreHeight = this->height( );
	if( thisCentreHeight > 0 ) {
		// 当前组件宽度
		int thisCentreWidthWidth = this->width( );
		if( thisCentreWidthWidth > 0 ) {
			int favoriteWidth = musicWidgetSizeInfo->getFavoriteWidth( );
			int titleHeight = musicWidgetSizeInfo->getTitleHeight( );
			musicfavoriteWidgetScrollArea->setGeometry( 0, 0, favoriteWidth, thisCentreHeight );
			int modeWidth = thisCentreWidthWidth - favoriteWidth;
			musicTitleWidgetScrollArea->setGeometry( favoriteWidth, 0, modeWidth, titleHeight );
			int modHeight = thisCentreHeight - titleHeight;
			musicListWidgetScrollArea->setGeometry( favoriteWidth, titleHeight, modeWidth, modHeight );
			return userMutex->result_unlock( true );
		}
		return userMutex->result_unlock( Result_Var_Function_Messag_Ptr_Out_Args( false, this, calculateSize, tr( "宽度失效:%1" ).arg(thisCentreWidthWidth ) ) );
	}
	return userMutex->result_unlock( Result_Var_Function_Messag_Ptr_Out_Args( false, this, calculateSize, tr( "高度失效:%1" ).arg( thisCentreHeight ) ) );
}
bool MusicCentreWidget::getJsonData( QJsonObject &get_json_object ) const {
	if( musicTitleWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicTitleWidget, getJsonData, tr( "未配置组件" ) );
	if( musicFavoriteWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteWidget, getJsonData, tr( "未配置组件" ) );
	if( musicListWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListWidget, getJsonData, tr( "未配置组件" ) );
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
	if( musicTitleWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicTitleWidget, setJsonData, tr( "未配置组件" ) );
	if( musicFavoriteWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteWidget, setJsonData, tr( "未配置组件" ) );
	if( musicListWidget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListWidget, setJsonData, tr( "未配置组件" ) );
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
	return InstanceTools::getAppMenuManage( )->getMusicFavoriteMenu( );
}
IMusicListMenu * MusicCentreWidget::getMusicListMenu( ) const {
	return InstanceTools::getAppMenuManage( )->getMusicListMenu( );
}
IMusicWidgetSizeInfo * MusicCentreWidget::getMusicWidgetSizeInfo( ) const {
	return InstanceTools::getAppDataManage( )->getMusicWidgetSizeInfo( );
}

IMusicFavoriteWidget * MusicCentreWidget::setMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) {
	if( music_favorite_widget == nullptr ) {
		auto old = this->musicFavoriteWidget;
		if( musicFavoriteWidget && musicFavoriteWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( music_favorite_widget, musicFavoriteWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		this->musicFavoriteWidget = music_favorite_widget;
		musicfavoriteWidgetScrollArea->takeWidget( );
		return old;
	}
	QWidget *widget = music_favorite_widget->toWidget( );
	if( widget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_favorite_widget, music_favorite_widget, toWidget, tr( "不存在配置的 QWidget 组件失败" ) );
	if( music_favorite_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_favorite_widget, music_favorite_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicFavoriteWidget && musicFavoriteWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_favorite_widget, musicFavoriteWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	auto old = this->musicFavoriteWidget;
	this->musicFavoriteWidget = music_favorite_widget;
	musicfavoriteWidgetScrollArea->takeWidget( );
	musicfavoriteWidgetScrollArea->setWidget( widget );
	return old;
}
IMusicListWidget * MusicCentreWidget::setMusicListWidget( IMusicListWidget *const music_list_widget ) {
	if( music_list_widget == nullptr ) {
		auto old = this->musicListWidget;
		if( musicListWidget && musicListWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( music_list_widget, musicListWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		this->musicListWidget = music_list_widget;
		musicListWidgetScrollArea->takeWidget( );
		return old;
	}
	QWidget *widget = music_list_widget->toWidget( );
	if( widget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_list_widget, music_list_widget, toWidget, tr( "不存在配置的 QWidget 组件失败" ) );
	if( music_list_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_list_widget, music_list_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicListWidget && musicListWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_list_widget, musicListWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	auto old = this->musicListWidget;
	this->musicListWidget = music_list_widget;
	musicListWidgetScrollArea->takeWidget( );
	musicListWidgetScrollArea->setWidget( widget );
	repaintListWidget( );
	return old;
}
IMusicTitleWidget * MusicCentreWidget::setMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) {
	if( music_title_widget == nullptr ) {
		auto old = this->musicTitleWidget;
		if( musicTitleWidget && musicTitleWidget->setMusicCentreWidget( nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( music_title_widget, musicTitleWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
		this->musicTitleWidget = music_title_widget;
		musicTitleWidget->setIMusicItemWidthInfo( nullptr );
		musicTitleWidgetScrollArea->takeWidget( );
		return old;
	}
	QWidget *widget = music_title_widget->toWidget( );
	if( widget == nullptr )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_title_widget, music_title_widget, toWidget, tr( "不存在配置的 QWidget 组件失败" ) );
	if( music_title_widget->setMusicCentreWidget( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_title_widget, music_title_widget, setMusicCentreWidget, tr( "配置 MusicCentreWidget 组件失败" ) );
	if( musicTitleWidget && musicTitleWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( music_title_widget, musicTitleWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	auto old = this->musicTitleWidget;
	this->musicTitleWidget = music_title_widget;
	musicTitleWidgetScrollArea->takeWidget( );
	musicTitleWidgetScrollArea->setWidget( widget );
	repaintTitleWidget( );
	return old;
}
IMusicFavoriteWidget * MusicCentreWidget::removeMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) {
	if( music_favorite_widget == nullptr )
		return nullptr;
	if( musicFavoriteWidget == nullptr )
		return nullptr;
	auto thisFavoriteWidget = musicFavoriteWidget->toWidget( );
	auto removeFavoriteWidget = music_favorite_widget->toWidget( );
	if( thisFavoriteWidget != removeFavoriteWidget )
		return nullptr;
	if( musicFavoriteWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( musicFavoriteWidget, musicFavoriteWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	musicFavoriteWidget = nullptr;
	return music_favorite_widget;
}
IMusicListWidget * MusicCentreWidget::removeMusicListWidget( IMusicListWidget *const music_list_widget ) {
	if( music_list_widget == nullptr )
		return nullptr;
	if( musicListWidget == nullptr )
		return nullptr;
	auto thisWidget = musicListWidget->toWidget( );
	auto removeWidget = music_list_widget->toWidget( );
	if( thisWidget != removeWidget )
		return nullptr;
	if( musicListWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( musicListWidget, musicListWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	musicListWidget = nullptr;
	return music_list_widget;
}
IMusicTitleWidget * MusicCentreWidget::removeMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) {
	if( music_title_widget == nullptr )
		return nullptr;
	if( musicTitleWidget == nullptr )
		return nullptr;
	auto thisWidget = musicTitleWidget->toWidget( );
	auto removeWidget = music_title_widget->toWidget( );
	if( thisWidget != removeWidget )
		return nullptr;
	if( musicTitleWidget->setMusicCentreWidget( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( musicTitleWidget, musicTitleWidget, setMusicCentreWidget, tr( "配置 nullptr 组件失败" ) );
	musicTitleWidget = nullptr;
	return music_title_widget;
}

bool MusicCentreWidget::repaintListWidget( ) {
	return true;
}
bool MusicCentreWidget::repaintTitleWidget( ) {
	return true;
}
bool MusicCentreWidget::repaintFavoriteWidget( ) {
	return true;
}
bool MusicCentreWidget::synchronizationChildrenWidgetSize( ) {
	return calculateSize( );
}
