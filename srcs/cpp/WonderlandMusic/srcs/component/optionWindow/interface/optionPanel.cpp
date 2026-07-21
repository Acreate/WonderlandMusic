#include "optionPanel.h"
#include "../optionWindow.h"
#include "../optionItem/optionItem.h"

OptionPanel::OptionPanel( OptionWindow *option_window ) : OptionPanel( option_window, "", QImage( ) ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QString &name ) : OptionPanel( option_window, name, QImage( ) ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QImage &icon ) : OptionPanel( option_window, "", icon ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QString &name, const QImage &icon ) : optionWindow( option_window ), name( name ), icon( icon ) {
	optionItem = new OptionItem( OptionItem::Show_Type::All );
}

OptionPanel::~OptionPanel( ) {
	emit optionItem->signal_delete_OptionPanel( this );
	delete optionItem;
}

OptionWindow * OptionPanel::getOptionWindow( ) const {
	return optionWindow;
}

OptionItem * OptionPanel::getOptionItem( ) const {
	return optionItem;
}

const QString & OptionPanel::getName( ) const {
	return name;
}

void OptionPanel::setName( const QString &name ) {
	this->name = name;
}

const QImage & OptionPanel::getIcon( ) const {
	return icon;
}

void OptionPanel::setIcon( const QImage &icon ) {
	this->icon = icon;
}

void OptionPanel::updateInfo( ) {
	optionWindow->updateOptionPanelInfo( this );
}
