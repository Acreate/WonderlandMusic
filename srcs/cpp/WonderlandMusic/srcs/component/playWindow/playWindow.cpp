#include "playWindow.h"

#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../mutex/userMutex.h"

#include "interface/iPlayerControlWidget.h"
#include "interface/iPlayerInfoListWidget.h"

#include "playWindowChildWidgetScrallArea/playerControlWidgetScrollArea.h"
#include "playWindowChildWidgetScrallArea/playerInfoListWidgetScrollArea.h"
PlayWindow::PlayWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {
}
PlayWindow::~PlayWindow( ) {
	deleteResource( );
}
bool PlayWindow::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	if( playerInfoListWidget )
		playerInfoListWidget->setPlayerWindow( nullptr );
	if( playerControlWidget )
		playerControlWidget->setPlayerWindow( nullptr );
	userMutex->lock( );
	playerControlWidgetScrollArea->takeWidget( );
	playerInfoListWidgetScrollArea->takeWidget( );
	playerInfoListWidget = nullptr;
	playerControlWidget = nullptr;
	Delete_Resource_App_Core_Ptr( playerControlWidgetScrollArea );
	Delete_Resource_App_Core_Ptr( playerInfoListWidgetScrollArea );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
bool PlayWindow::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	playerControlWidgetScrollArea = new PlayerControlWidgetScrollArea( this );
	playerInfoListWidgetScrollArea = new PlayerInfoListWidgetScrollArea( this );
	return true;
}
bool PlayWindow::init( ) {
	return true;
}
bool PlayWindow::initAfter( ) {
	return true;
}
IPlayerInfoListWidget * PlayWindow::getPlayerInfoListWidget( ) const {
	return playerInfoListWidget;
}
IPlayerInfoListWidget * PlayWindow::setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget ) {
	if( playerInfoListWidget && playerInfoListWidget->setPlayerWindow( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( player_info_list_widget, playerInfoListWidget, setPlayerWindow, tr( "删除配置信息列表组件异常" ) );
	if( player_info_list_widget && player_info_list_widget->setPlayerWindow( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( player_info_list_widget, player_info_list_widget, setPlayerWindow, tr( "新配置信息列表组件异常" ) );
	auto old = playerInfoListWidget;
	playerInfoListWidget = player_info_list_widget;
	updateLayout( );
	return old;
}
IPlayerControlWidget * PlayWindow::getPlayerControlWidget( ) const {
	return playerControlWidget;
}
IPlayerControlWidget * PlayWindow::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	if( playerControlWidget && playerControlWidget->setPlayerWindow( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( player_control_widget, playerControlWidget, setPlayerWindow, tr( "删除配置信息列表组件异常" ) );
	if( player_control_widget && player_control_widget->setPlayerWindow( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( player_control_widget, player_control_widget, setPlayerWindow, tr( "新配置信息列表组件异常" ) );
	auto old = playerControlWidget;
	playerControlWidget = player_control_widget;
	updateLayout( );
	return old;
}
bool PlayWindow::updateLayout( ) {
	if( playerControlWidget )
		if( playerControlWidget->updateLayout( ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerControlWidget, updateLayout, tr( "控制组件布局异常" ) );
	if( playerInfoListWidget )
		if( playerInfoListWidget->updateLayout( ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerInfoListWidget, updateLayout, tr( "列表组件布局异常" ) );

	return true;
}
