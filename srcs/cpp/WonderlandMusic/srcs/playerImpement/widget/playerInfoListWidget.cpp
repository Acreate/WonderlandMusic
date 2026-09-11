#include "playerInfoListWidget.h"

#include "../../component/playWindow/playWindow.h"
#include "../../component/playWindow/interface/widget/iPlayerWindowCentreWidget.h"

PlayerInfoListWidget::PlayerInfoListWidget( ) : ClassTypeInfoVar( ), OptionWindow( ), IPlayerInfoListWidget( ) {
	regClassTypeInfoRef( this );
}
QWidget * PlayerInfoListWidget::toWidget( ) {
	return this;
}
bool PlayerInfoListWidget::setPlayerWindowCentre( IPlayerWindowCentreWidget *player_window_centre_widget ) {
	playerWindowCentreWidget = player_window_centre_widget;

	QWidget *widget = nullptr;
	if( player_window_centre_widget )
		widget = playerWindowCentreWidget->toWidget( );
	setParent( widget );
	if( widget )
		show( );
	else
		hide( );
	return true;
}
IPlayerWindowCentreWidget * PlayerInfoListWidget::getPlayerWindowCentre( ) const {
	return playerWindowCentreWidget;
}
bool PlayerInfoListWidget::updateLayout( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	auto widget = playerWindowCentreWidget->toWidget( );
	int width = widget->width( );
	resize( width, 200 );
	return true;
}
PlayerInfoListWidget::~PlayerInfoListWidget( ) {
	if( playerWindowCentreWidget )
		playerWindowCentreWidget->setPlayerInfoListWidget( nullptr );
	playerWindowCentreWidget = nullptr;
	
}
