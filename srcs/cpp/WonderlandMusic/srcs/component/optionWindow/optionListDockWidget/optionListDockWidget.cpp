#include "optionListDockWidget.h"

#include <QMenu>
#include <QScrollArea>

#include "../optionWindow.h"

#include "../../../head/after_init_macro.h"
#include "../../../head/before_init_macro.h"
#include "../../../head/init_macro.h"
#include "../../../head/release_macro.h"

#include "../widget/optionListWidget.h"
OptionListDockWidget::OptionListDockWidget( OptionWindow *option_window ) : optionWindow( option_window ) {
}
OptionWindow * OptionListDockWidget::getOptionWindow( ) const {
	return optionWindow;
}
QScrollArea * OptionListDockWidget::getScrollArea( ) const {
	return scrollArea;
}
OptionListWidget * OptionListDockWidget::getOptionListWidget( ) const {
	return optionListWidget;
}
void OptionListDockWidget::updateOptionButtonLayout( ) {
	optionListWidget->updateOptionButtonLayout( );
}
int OptionListDockWidget::getSuggestWidth( ) const {
	return optionListWidget->getSuggestWidth( );
}
int OptionListDockWidget::getSuggestHeight( ) const {
	return optionListWidget->getSuggestHeight( );
}
QSize OptionListDockWidget::getSuggestSize( ) const {
	return optionListWidget->getSuggestSize( );
}
bool OptionListDockWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( dockTitleWidget );
	return true;
}
bool OptionListDockWidget::initBefore( ) {
	deleteResource( );
	if( optionWindow == nullptr )
		return false;
	dockTitleWidget = new QWidget;
	scrollArea = new QScrollArea;
	optionListWidget = new OptionListWidget( optionWindow );

	Before_Init_Resource_App_Core_Ptr( optionListWidget );
	return true;
}
bool OptionListDockWidget::init( ) {
	Init_Resource_App_Core_Ptr( optionListWidget );
	return true;
}
bool OptionListDockWidget::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( optionListWidget );
	scrollArea->setWidget( optionListWidget );
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidget( scrollArea );
	setTitleBarWidget( dockTitleWidget );
	setContextMenuPolicy( Qt::NoContextMenu );
	setFeatures( QDockWidget::NoDockWidgetFeatures );
	setAllowedAreas( Qt::LeftDockWidgetArea );
	setFloating( false );
	optionWindow->addDockWidget( Qt::LeftDockWidgetArea, this );

	return true;
}
