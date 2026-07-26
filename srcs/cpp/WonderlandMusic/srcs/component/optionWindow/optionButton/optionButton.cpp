#include "optionButton.h"
#include <QPainter>
#include "../../../application/appDrawManage.h"
#include "../../../application/appInstance.h"
#include "../../../application/appRenderImage.h"
#include "../../../application/appUserInterfaceManage.h"

#include "../widget/optionListWidget.h"

const QString & OptionButton::getName( ) const {
	return *name;
}
const QImage & OptionButton::getIcon( ) const {
	return *icon;
}
void OptionButton::setName( const QString &name ) {
	*this->name = name;
}
void OptionButton::setIcon( const QImage &icon ) {
	*this->icon = icon;
}
OptionButton::~OptionButton( ) {
	delete name;
	delete icon;
}
OptionButton::OptionButton( OptionWindow *option_window, const QString &name, const QImage &icon ) : optionWindow( option_window ), name( new QString( name ) ), icon( new QImage( icon ) ) {
	updateSize( );
}

bool OptionButton::isClick( ) const {
	return click;
}
OptionButton::Show_Type OptionButton::getShow( ) const {
	return show;
}
void OptionButton::setShow( const Show_Type show ) {
	this->show = show;
	update( );
}
QSize OptionButton::updateSize( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto userInterfaceManage = appInstance->getAppUserInterfaceManage( );
	auto appDrawManage = userInterfaceManage->getAppDrawManage( );
	auto appRenderImage = appDrawManage->getAppRenderImage( );
	QSize result( 0, 0 );

	switch( show ) {
		case Show_Type::Txt :
			appRenderImage->getTxtSize( result, *name );
			break;
		case Show_Type::Icon :
			result = this->icon->size( );
			break;
		case Show_Type::All : {
			appRenderImage->getTxtSize( result, *name );
			int w = result.width( );
			auto icon = this->icon->scaledToWidth( w );
			result.setWidth( icon.width( ) + w );
		}
		break;
	}
	setFixedSize( result );
	return result;
}

void OptionButton::paintEvent( QPaintEvent *paint_event ) {
	int height = this->height( );
	if( height == 0 )
		return;
	QPainter painter( this );
	int offsetX = 0;
	QImage renderIcon;
	switch( show ) {
		case Show_Type::Txt : {
			if( name->isEmpty( ) == false ) {
				auto appInstance = AppInstance::getAppInstance( );
				auto interfaceManage = appInstance->getAppUserInterfaceManage( );
				auto appDrawManage = interfaceManage->getAppDrawManage( );
				auto appRenderImage = appDrawManage->getAppRenderImage( );
				if( appRenderImage->renderTxt( renderIcon, *name ) ) {
					renderIcon = renderIcon.scaledToHeight( height );
					painter.drawImage( offsetX, 0, renderIcon );
				}
			}
		}
		break;
		case Show_Type::Icon : {
			if( icon->isNull( ) == false ) {
				renderIcon = icon->scaledToHeight( height );
				painter.drawImage( 0, 0, renderIcon );
			}
		}
		break;
		case Show_Type::All : {
			if( icon->isNull( ) == false ) {
				renderIcon = icon->scaledToHeight( height );
				painter.drawImage( 0, 0, renderIcon );
				offsetX += icon->width( );
			}
			if( name->isEmpty( ) == false ) {
				auto appInstance = AppInstance::getAppInstance( );
				auto interfaceManage = appInstance->getAppUserInterfaceManage( );
				auto appDrawManage = interfaceManage->getAppDrawManage( );
				auto appRenderImage = appDrawManage->getAppRenderImage( );
				if( appRenderImage->renderTxt( renderIcon, *name ) ) {
					renderIcon = renderIcon.scaledToHeight( height );
					painter.drawImage( offsetX, 0, renderIcon );
				}
			}
		}
		break;
	}
}

void OptionButton::mousePressEvent( QMouseEvent *event ) {
	click = true;
}

void OptionButton::mouseReleaseEvent( QMouseEvent *event ) {
	if( click )
		emit signal_click_item( this );
	click = false;
}

void OptionButton::enterEvent( QEnterEvent *event ) {
	click = false;
}

void OptionButton::leaveEvent( QEvent *event ) {
	click = false;
}
