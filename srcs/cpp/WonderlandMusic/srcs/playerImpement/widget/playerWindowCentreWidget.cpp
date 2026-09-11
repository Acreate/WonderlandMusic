#include "playerWindowCentreWidget.h"

#include "../../component/playWindow/interface/widget/iPlayerControlWidget.h"
#include "../../component/playWindow/interface/widget/iPlayerInfoListWidget.h"
#include "../../component/playWindow/playerWindowCentreChildWidgetScrallArea/playerControlWidgetScrollArea.h"
#include "../../component/playWindow/playerWindowCentreChildWidgetScrallArea/playerInfoListWidgetScrollArea.h"

#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../mutex/userMutex.h"
PlayerWindowCentreWidget::PlayerWindowCentreWidget( ) {
	regClassTypeInfoRef( this );
}
PlayerWindowCentreWidget::~PlayerWindowCentreWidget( ) {
	deleteResource( );
	
}
PlayWindow * PlayerWindowCentreWidget::getPlayWindow( ) const {
	return playWindow;
}
bool PlayerWindowCentreWidget::setPlayWindow( PlayWindow *play_window ) {
	auto old = playWindow;
	playWindow = play_window;
	return old;
}
bool PlayerWindowCentreWidget::setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget ) {
	if( playerInfoListWidget && playerInfoListWidget->setPlayerWindowCentre( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, playerInfoListWidget, setPlayerWindow, tr( "删除配置信息列表组件异常" ) );
	if( player_info_list_widget && player_info_list_widget->setPlayerWindowCentre( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, player_info_list_widget, setPlayerWindow, tr( "新配置信息列表组件异常" ) );
	playerInfoListWidget = player_info_list_widget;
	updateLayout( );
	return true;
}
bool PlayerWindowCentreWidget::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	if( playerControlWidget && playerControlWidget->setPlayerWindowCentre( nullptr ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, playerControlWidget, setPlayerWindow, tr( "删除配置信息列表组件异常" ) );
	if( player_control_widget && player_control_widget->setPlayerWindowCentre( this ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, player_control_widget, setPlayerWindow, tr( "新配置信息列表组件异常" ) );
	playerControlWidget = player_control_widget;
	updateLayout( );
	return true;
}
QWidget * PlayerWindowCentreWidget::toWidget( ) {
	return this;
}
bool PlayerWindowCentreWidget::updateLayout( ) {
	if( playerControlWidget )
		if( playerControlWidget->updateLayout( ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerControlWidget, updateLayout, tr( "控制组件布局异常" ) );
	if( playerInfoListWidget )
		if( playerInfoListWidget->updateLayout( ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerInfoListWidget, updateLayout, tr( "列表组件布局异常" ) );

	return true;
}
IPlayerInfoListWidget * PlayerWindowCentreWidget::getPlayerInfoListWidget( ) const {
	return playerInfoListWidget;
}
IPlayerControlWidget * PlayerWindowCentreWidget::getPlayerControlWidget( ) const {
	return playerControlWidget;
}
bool PlayerWindowCentreWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	if( playerInfoListWidget )
		playerInfoListWidget->setPlayerWindowCentre( nullptr );
	if( playerControlWidget )
		playerControlWidget->setPlayerWindowCentre( nullptr );
	userMutex->lock( );
	playerControlWidgetScrollArea->takeWidget( );
	playerInfoListWidgetScrollArea->takeWidget( );
	Delete_Resource_App_Core_Ptr( playerControlWidgetScrollArea );
	Delete_Resource_App_Core_Ptr( playerInfoListWidgetScrollArea );
	playerInfoListWidget = nullptr;
	playerControlWidget = nullptr;
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
bool PlayerWindowCentreWidget::initBefore( ) {
	deleteResource( );
	playerControlWidgetScrollArea = new PlayerControlWidgetScrollArea( );
	playerInfoListWidgetScrollArea = new PlayerInfoListWidgetScrollArea( );
	return true;
}
bool PlayerWindowCentreWidget::init( ) {
	return true;
}
bool PlayerWindowCentreWidget::initAfter( ) {
	return true;
}
