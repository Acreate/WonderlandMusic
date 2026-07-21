#include "optionItem.h"
#include "../optionWindow.h"
#include "../interface/optionPanel.h"

OptionItem::~OptionItem( ) {
}

OptionItem::OptionItem( Show_Type show_type ) : showType( show_type ) {
}

const QString & OptionItem::getName( ) const {
	return optionPanel->getName( );
}

void OptionItem::setName( const QString &name ) {
	optionPanel->setName( name );
}

const QImage & OptionItem::getIcon( ) const {
	return optionPanel->getIcon( );
}

void OptionItem::setIcon( const QImage &icon ) {
	optionPanel->setIcon( icon );
}

OptionItem::Show_Type OptionItem::getShowType( ) const {
	return showType;
}

void OptionItem::setShowType( const Show_Type show_type ) {
	showType = show_type;
}

OptionPanel * OptionItem::getOptionPanel( ) const {
	return optionPanel;
}
