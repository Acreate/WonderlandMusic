#include "playerControlWidget.h"

#include <QMouseEvent>

#include <component/playWindow/interface/widget/iPlayerWindowCentreWidget.h>

#include "../../component/playWindow/interface/playerComponent/iPlayerSortOption.h"
#include "../../component/playWindow/interface/playerComponent/iPlayerbackProgressBar.h"
#include "../../component/playWindow/interface/playerComponent/iPlayerSelectOption.h"

#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../mutex/userMutex.h"

PlayerControlWidget::PlayerControlWidget( ) {
	regClassTypeInfoRef( this );
}
PlayerControlWidget::~PlayerControlWidget( ) {
	deleteResource( );
}
QWidget * PlayerControlWidget::toWidget( ) {
	return this;
}
bool PlayerControlWidget::setPlayerWindowCentre( IPlayerWindowCentreWidget *play_window_centre_widget ) {
	if( play_window_centre_widget ) {
		auto widget = play_window_centre_widget->toWidget( );
		if( widget ) {
			setParent( widget );
			show( );
		} else {
			setParent( nullptr );
			hide( );
		}
	} else {
		setParent( nullptr );
		hide( );
	}
	playerWindowCentreWidget = play_window_centre_widget;
	return true;
}
IPlayerWindowCentreWidget * PlayerControlWidget::getPlayerWindowCentre( ) const {
	return playerWindowCentreWidget;
}
bool PlayerControlWidget::updateLayout( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	if( isHidden( ) == true )
		return false;

	return true;
}
bool PlayerControlWidget::player( const QString &music_file_path ) {
	return false;
}
bool PlayerControlWidget::stop( ) {
	return false;
}
bool PlayerControlWidget::terminate( ) {
	return false;
}
bool PlayerControlWidget::setPlayerTime( const int64_t &player_mill_second_time ) {
	return false;
}
IPlayerSortOption * PlayerControlWidget::getPlayerSortOption( ) const {
	return playerSortOption;
}
IPlayerSelectOption * PlayerControlWidget::getPlayerSelectOption( ) const {
	return playerSelectOption;
}
IPlayerbackProgressBar * PlayerControlWidget::getPlayerbackProgressBar( ) const {
	return playerbackProgressBar;
}
bool PlayerControlWidget::setPlayerSortOption( IPlayerSortOption *player_sort_option ) {
	if( player_sort_option ) {
		if( IPlayerControlWidget::setPlayerSortOption( player_sort_option, this ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, player_sort_option, setPlayerSortOption, tr( "父类设置控住组件异常" ) );
	}
	auto old = playerSortOption;
	playerSortOption = player_sort_option;
	if( old )
		if( IPlayerControlWidget::setPlayerSortOption( old, nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, old, setPlayerSortOption, tr( "父类设置控制组件异常-nullptr" ) );
	return true;
}
bool PlayerControlWidget::setPlayerSelectOption( IPlayerSelectOption *player_select_option ) {
	if( player_select_option ) {
		if( IPlayerControlWidget::setPlayerSelectOption( player_select_option, this ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, player_select_option, setPlayerSelectOption, tr( "父类设置控住组件异常" ) );
	}
	auto old = playerSelectOption;
	playerSelectOption = player_select_option;
	if( old )
		if( IPlayerControlWidget::setPlayerSelectOption( old, nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, old, setPlayerSelectOption, tr( "父类设置控制组件异常-nullptr" ) );
	return true;
}
bool PlayerControlWidget::setPlayerbackProgressBar( IPlayerbackProgressBar *playerback_progress_bar ) {
	if( playerback_progress_bar ) {
		if( IPlayerControlWidget::setPlayerbackProgressBar( playerback_progress_bar, this ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, playerback_progress_bar, setPlayerbackProgressBar, tr( "父类设置控住组件异常" ) );
	}
	auto old = playerbackProgressBar;
	userMutex->lock( );
	playerbackProgressBar = playerback_progress_bar;
	userMutex->unlock( );
	if( old )
		if( IPlayerControlWidget::setPlayerbackProgressBar( old, nullptr ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, old, setPlayerbackProgressBar, tr( "父类设置控制组件异常-nullptr" ) );
	return true;
}
bool PlayerControlWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	setPlayerWindowCentre( nullptr );
	setPlayerbackProgressBar( nullptr );
	setPlayerSortOption( nullptr );
	setPlayerSelectOption( nullptr );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void PlayerControlWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
void PlayerControlWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
}
void PlayerControlWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void PlayerControlWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void PlayerControlWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}

void PlayerControlWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateLayout( );
}
bool PlayerControlWidget::initBefore( ) {
	PlayerControlWidget::deleteResource( );
	setMouseTracking( true );
	return true;
}
bool PlayerControlWidget::init( ) {
	return true;
}
bool PlayerControlWidget::initAfter( ) {
	return true;
}
