#include "playerControlWidget.h"

#include <QMouseEvent>
#include <QPainter>

#include "../../component/playWindow/interface/widget/iPlayerWindowCentreWidget.h"

#include "../../head/release_macro.h"

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
bool PlayerControlWidget::deleteResource( ) {
	setPlayerWindowCentre( nullptr );
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
}
bool PlayerControlWidget::initBefore( ) {
	deleteResource( );
	setMouseTracking( true );
	return true;
}
bool PlayerControlWidget::init( ) {
	return true;
}
bool PlayerControlWidget::initAfter( ) {
	return true;
}
