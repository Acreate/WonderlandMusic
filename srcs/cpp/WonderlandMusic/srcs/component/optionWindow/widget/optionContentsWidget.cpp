#include "optionContentsWidget.h"

#include "../optionWindow.h"

#include "../../../head/release_macro.h"

#include "../../../mutex/userMutex.h"
OptionContentsWidget::~OptionContentsWidget( ) {
}
OptionContentsWidget::OptionContentsWidget( OptionWindow *parent ) : QWidget( parent ), listParentWindow( parent ) {
}
void OptionContentsWidget::showOptionPanel( OptionPanel *option_panel ) {
}
void OptionContentsWidget::addOptionPanel( OptionPanel *option_panel ) {
}
void OptionContentsWidget::deleteOptionPanel( OptionPanel *option_panel ) {
}
bool OptionContentsWidget::hasOptionPanel( size_t &result_index, const OptionPanel *option_panel ) {
	return false;
}
void OptionContentsWidget::updateOptionPanelLayout( ) {
}
int OptionContentsWidget::getSuggestWidth( ) const {
	return 0;
}
int OptionContentsWidget::getSuggestHeight( ) const {
	return 0;
}
QSize OptionContentsWidget::getSuggestSize( ) const {
	return { };
}
bool OptionContentsWidget::deleteResource( ) {
	if( userMutex ) {
		userMutex->lock( );
		listParentWindow->setCentralWidget( nullptr );
		optionPanelVector.clear( );
		userMutex->unlock( );
		Delete_Resource_App_Core_Ptr( userMutex );
	}
	return true;
}
bool OptionContentsWidget::initBefore( ) {
	deleteResource( );
	return true;
}
bool OptionContentsWidget::init( ) {
	return true;
}
bool OptionContentsWidget::initAfter( ) {
	listParentWindow->setCentralWidget( this );
	return true;
}
