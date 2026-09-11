#include "playerInfoListWidget.h"

#include "../../component/playWindow/playWindow.h"
#include "../../component/playWindow/interface/widget/iPlayerWindowCentreWidget.h"

#include "../../head/release_macro.h"

bool PlayerInfoListWidget::deleteResource( ) {
	bool result = OptionWindow::deleteResource( );
	if( result == false )
		return result;
	setPlayerWindowCentre( nullptr );
	return result;
}
bool PlayerInfoListWidget::init( ) {
	bool result = OptionWindow::init( );

	return result;
}
bool PlayerInfoListWidget::initAfter( ) {
	bool result = OptionWindow::initAfter( );

	return result;
}
bool PlayerInfoListWidget::initBefore( ) {
	PlayerInfoListWidget::deleteResource( );
	bool result = OptionWindow::initBefore( );

	return result;
}
PlayerInfoListWidget::PlayerInfoListWidget( ) : ClassTypeInfoVar( ), OptionWindow( ), IPlayerInfoListWidget( ) {
	regClassTypeInfoRef( this );
}
QWidget * PlayerInfoListWidget::toWidget( ) {
	return this;
}
bool PlayerInfoListWidget::setPlayerWindowCentre( IPlayerWindowCentreWidget *player_window_centre_widget ) {
	if( player_window_centre_widget ) {
		QWidget *widget = player_window_centre_widget->toWidget( );

		if( widget ) {
			show( );
			setParent( widget );
		} else {
			hide( );
			setParent( nullptr );
		}
	} else {
		hide( );
		setParent( nullptr );
	}
	playerWindowCentreWidget = player_window_centre_widget;
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
	deleteResource( );
}
