#include "optionContentsScroll.h"

#include "../../../head/after_init_macro.h"
#include "../../../head/before_init_macro.h"
#include "../../../head/init_macro.h"
#include "../../../head/release_macro.h"

#include "../widget/optionContentsWidget.h"
OptionContentsScroll::OptionContentsScroll( OptionWindow *option_window ) : optionWindow( option_window ) {
}
OptionContentsScroll::~OptionContentsScroll( ) {
}
bool OptionContentsScroll::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( optionContentsWidget );
	return true;
}
bool OptionContentsScroll::initBefore( ) {
	optionContentsWidget = new OptionContentsWidget( optionWindow );

	Before_Init_Resource_App_Core_Ptr( optionContentsWidget );
	return true;
}
bool OptionContentsScroll::init( ) {
	Init_Resource_App_Core_Ptr( optionContentsWidget );
	return true;
}
bool OptionContentsScroll::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( optionContentsWidget );
	return true;
}
