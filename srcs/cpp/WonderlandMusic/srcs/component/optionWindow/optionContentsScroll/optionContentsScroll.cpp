#include "optionContentsScroll.h"

#include "../optionWindow.h"

#include "../interface/optionPanel.h"

OptionContentsScroll::OptionContentsScroll( OptionWindow *option_window ) : optionWindow( option_window ) {
}
OptionContentsScroll::~OptionContentsScroll( ) {
}
bool OptionContentsScroll::deleteResource( ) {
	return true;
}
void OptionContentsScroll::hideOptionPanel( OptionPanel *option_panel ) {
	if( option_panel == nullptr )
		return;
	if( currentOptionPanel == option_panel ) {
		auto widget = currentOptionPanel->toWidget( );
		if( widget ) {
			takeWidget( );
			widget->hide( );
			setWidget( nullptr );
		}
		currentOptionPanel = nullptr;
	}
}
void OptionContentsScroll::showOptionPanel( OptionPanel *option_panel ) {
	if( option_panel == nullptr )
		return;

	hideOptionPanel( );

	auto widget = option_panel->toWidget( );
	if( widget ) {
		takeWidget( );
		setWidget( widget );
	}
	currentOptionPanel = option_panel;
}
void OptionContentsScroll::hideOptionPanel( ) {
	if( currentOptionPanel ) {
		auto widget = currentOptionPanel->toWidget( );
		if( widget ) {
			takeWidget( );
			widget->hide( );
			setWidget( nullptr );
		}
		currentOptionPanel = nullptr;
	}
}
void OptionContentsScroll::showOptionPanel( ) {
	if( currentOptionPanel ) {
		auto widget = currentOptionPanel->toWidget( );
		if( widget ) {
			takeWidget( );
			setWidget( widget );
		}
		currentOptionPanel = nullptr;
	}
}
bool OptionContentsScroll::initBefore( ) {
	deleteResource( );

	return true;
}
bool OptionContentsScroll::init( ) {
	return true;
}
bool OptionContentsScroll::initAfter( ) {
	setWidgetResizable( true );
	optionWindow->setCentralWidget( this );
	return true;
}
