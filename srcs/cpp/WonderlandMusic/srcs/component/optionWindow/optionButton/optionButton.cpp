#include "optionButton.h"
#include <QPainter>

#include "../optionWindow.h"

#include "../../../application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h"

#include "../../../head/result_message_out.h"

#include "../../../tools/instanceTools.h"
#include "../interface/optionPanel.h"

OptionButton::~OptionButton( ) {
}
OptionButton::OptionButton( OptionWindow *option_window ) : optionWindow( option_window ) {
	startOffsetX = 5;
	startOffsetY = 5;
}

bool OptionButton::isClick( ) const {
	return click;
}
OptionButton::Show_Type OptionButton::getShowType( ) const {
	return showType;
}
void OptionButton::setShowType( const Show_Type show ) {
	showType = show;
	updateSize( );
	update( );
}
QSize OptionButton::updateSize( ) {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	QSize result( 0, 0 );

	switch( showType ) {
		case Show_Type::Txt :
			appRenderImage->getTxtSize( result, optionPanel->getName( ) );
			break;
		case Show_Type::Icon : {
			auto &image = optionPanel->getIcon( );
			if( image.isNull( ) )
				break;
			result = image.size( );
		}
		break;
		case Show_Type::All : {
			appRenderImage->getTxtSize( result, optionPanel->getName( ) );
			auto &image = optionPanel->getIcon( );
			if( image.isNull( ) == false ) {
				int w = result.width( );
				auto icon = image.scaledToWidth( w );
				result.setWidth( icon.width( ) + w );
				break;
			}
		}
		break;
	}
	result = QSize( result.width( ) + startOffsetX * 2, result.height( ) + startOffsetY * 2 );
	setFixedSize( result );
	return result;
}

void OptionButton::paintEvent( QPaintEvent *paint_event ) {
	if( optionPanel == nullptr )
		return;
	int height = this->height( );
	if( height == 0 )
		return;
	QPainter painter( this );
	int offsetX = startOffsetX;
	int offsetY = startOffsetY;
	height -= startOffsetY * 2;
	QImage renderIcon;
	switch( showType ) {
		case Show_Type::Txt : {
			auto &name = optionPanel->getName( );
			if( name.isEmpty( ) == false ) {
				auto appRenderImage = InstanceTools::getAppRenderImage( );
				if( appRenderImage->renderTxt( renderIcon, name ) ) {
					renderIcon = renderIcon.scaledToHeight( height );
					painter.drawImage( offsetX, offsetY, renderIcon );
				}
			}
		}
		break;
		case Show_Type::Icon : {
			auto &icon = optionPanel->getIcon( );
			if( icon.isNull( ) == false ) {
				renderIcon = icon.scaledToHeight( height );
				painter.drawImage( offsetX, offsetY, renderIcon );
			}
		}
		break;
		case Show_Type::All : {
			auto &icon = optionPanel->getIcon( );
			if( icon.isNull( ) == false ) {
				renderIcon = icon.scaledToHeight( height );
				painter.drawImage( offsetX, offsetY, renderIcon );
				offsetX += icon.width( );
			}
			auto &name = optionPanel->getName( );
			if( name.isEmpty( ) == false ) {
				auto appRenderImage = InstanceTools::getAppRenderImage( );
				if( appRenderImage->renderTxt( renderIcon, name ) ) {
					renderIcon = renderIcon.scaledToHeight( height );
					painter.drawImage( offsetX, offsetY, renderIcon );
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
	if( click && optionWindow )
		if( optionWindow->showOptionButton( this ) == false )
			Result_Var_Messag_Out_Ptr_Function( optionWindow, showOptionButton( this ) );
	click = false;
}

void OptionButton::enterEvent( QEnterEvent *event ) {
	click = false;
}

void OptionButton::leaveEvent( QEvent *event ) {
	click = false;
}
