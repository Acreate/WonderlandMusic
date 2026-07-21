#include "optionButton.h"
#include <QPainter>
#include "../../../application/appDrawManage.h"
#include "../../../application/appInstance.h"
#include "../../../application/appRenderImage.h"
#include "../../../application/appUserInterfaceManage.h"
#include "../optionItem/optionItem.h"

OptionButton::OptionButton( OpetionListWidget *opetion_list_widget, OptionItem *bind_item ) : opetionListWidget( opetion_list_widget ),
	bindItem( bind_item ) {
}

OptionButton::~OptionButton( ) {
}

OpetionListWidget * OptionButton::getOpetionListWidget( ) const {
	return opetionListWidget;
}

OptionItem * OptionButton::getBindItem( ) const {
	return bindItem;
}

bool OptionButton::isClick( ) const {
	return click;
}

void OptionButton::paintEvent( QPaintEvent *paint_event ) {
	QPainter painter( this );
	int offsetX = 0;
	int height = this->height( );
	QImage icon;

	switch( bindItem->getShowType( ) ) {
		case OptionItem::Show_Type::Txt : {
			auto name = bindItem->getName( );
			if( name.isEmpty( ) == false ) {
				auto appInstance = AppInstance::getAppInstance( );
				auto interfaceManage = appInstance->getAppUserInterfaceManage( );
				auto appDrawManage = interfaceManage->getAppDrawManage( );
				auto appRenderImage = appDrawManage->getAppRenderImage( );
				if( appRenderImage->renderTxt( icon, name ) ) {
					icon = icon.scaledToHeight( height );
					painter.drawImage( offsetX, 0, icon );
					offsetX += icon.width( );
				}
			}
		}
		break;
		case OptionItem::Show_Type::Icon : {
			icon = bindItem->getIcon( );
			if( icon.isNull( ) == false ) {
				icon = icon.scaledToHeight( height );
				painter.drawImage( 0, 0, icon );
				offsetX += icon.width( );
			}
		}
		break;
		case OptionItem::Show_Type::All : {
			icon = bindItem->getIcon( );
			if( icon.isNull( ) == false ) {
				icon = icon.scaledToHeight( height );
				painter.drawImage( 0, 0, icon );
				offsetX += icon.width( );
			}
			auto name = bindItem->getName( );
			if( name.isEmpty( ) == false ) {
				auto appInstance = AppInstance::getAppInstance( );
				auto interfaceManage = appInstance->getAppUserInterfaceManage( );
				auto appDrawManage = interfaceManage->getAppDrawManage( );
				auto appRenderImage = appDrawManage->getAppRenderImage( );
				if( appRenderImage->renderTxt( icon, name ) ) {
					icon = icon.scaledToHeight( height );
					painter.drawImage( offsetX, 0, icon );
					offsetX += icon.width( );
				}
			}
		}
		break;
	}
	if( offsetX > this->width( ) )
		setMinimumWidth( offsetX );
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
