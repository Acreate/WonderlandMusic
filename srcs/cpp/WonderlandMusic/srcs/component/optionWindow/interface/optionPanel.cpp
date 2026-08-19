#include "optionPanel.h"

#include "../optionWindow.h"

#include "../optionButton/optionButton.h"

OptionPanel::OptionPanel( ) : OptionPanel( "", QImage( ) ) {
}

OptionPanel::OptionPanel( const QString &name ) : OptionPanel( name, QImage( ) ) {
}

OptionPanel::OptionPanel( const QImage &icon ) : OptionPanel( "", icon ) {
}

OptionPanel::OptionPanel( const QString &name, const QImage &icon ) : name( new QString( name ) ), icon( new QImage( icon ) ) {
}

OptionPanel::~OptionPanel( ) {
	if( optionWindow )
		optionWindow->removeOptionPanel( this );
	delete name;
	delete icon;
}
void OptionPanel::setName( const QString &name ) {
	*this->name = name;
	if( optionButton == nullptr )
		return;
	optionButton->updateSize( );
}
void OptionPanel::setIcon( const QImage &icon ) {
	*this->icon = icon;
	if( optionButton == nullptr )
		return;
	optionButton->updateSize( );
}
const QString & OptionPanel::getName( ) const {
	return *name;
}
const QImage & OptionPanel::getIcon( ) const {
	return *icon;
}

OptionWindow * OptionPanel::getOptionWindow( ) const {
	return optionWindow;
}
