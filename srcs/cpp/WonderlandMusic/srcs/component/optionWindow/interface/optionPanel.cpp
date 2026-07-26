#include "optionPanel.h"

#include "../optionWindow.h"

#include "../optionButton/optionButton.h"

OptionPanel::OptionPanel( OptionWindow *option_window ) : OptionPanel( option_window, "", QImage( ) ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QString &name ) : OptionPanel( option_window, name, QImage( ) ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QImage &icon ) : OptionPanel( option_window, "", icon ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QString &name, const QImage &icon ) {
	if( option_window == nullptr )
		return;
	optionButton = new OptionButton( option_window, name, icon );
	if( option_window->addOptionPanel( this ) )
		optionWindow = option_window;
}

OptionPanel::~OptionPanel( ) {
	if( optionWindow )
		optionWindow->deleteOptionPanel( this );
	delete optionButton;
}
void OptionPanel::setName( const QString &name ) {
}
void OptionPanel::setIcon( const QImage &icon ) {
}
const QString & OptionPanel::getName( ) const {
	return optionButton->getName( );
}
const QImage & OptionPanel::getIcon( ) const {
	return optionButton->getIcon( );
}

OptionWindow * OptionPanel::getOptionWindow( ) const {
	return optionWindow;
}
