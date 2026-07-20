#include "optionPanel.h"
#include "../optionWindow.h"
#include "../optionItem/optionItem.h"

OptionPanel::OptionPanel( OptionWindow *option_window ) : OptionPanel( option_window, "", QIcon( ) ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QString &name ) : OptionPanel( option_window, name, QIcon( ) ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QIcon &icon ) : OptionPanel( option_window, "", icon ) {
}

OptionPanel::OptionPanel( OptionWindow *option_window, const QString &name, const QIcon &icon ) : optionWindow( option_window ), name( name ), icon( icon ) {
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

const QIcon & OptionPanel::getIcon( ) const {
	return icon;
}

void OptionPanel::setIcon( const QIcon &icon ) {
	this->icon = icon;
}

void OptionPanel::updateInfo( ) {
	optionWindow->updateOptionPanelInfo( this );
}
