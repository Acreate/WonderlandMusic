#include "optionListDockWidget.h"

#include <QMenu>
#include <QScrollArea>
#include <qlayout.h>
#include <qstyle.h>

#include "../optionWindow.h"

#include <head/after_init_macro.h>
#include <head/before_init_macro.h>
#include <head/init_macro.h>
#include <head/release_macro.h>

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
	optionListWidget->setSuggestSize( );
	int newWidth = optionListWidget->width( );
	auto verticalScrollBar = scrollArea->verticalScrollBar( );
	if( verticalScrollBar && scrollArea->isVisible( ) ) {
		auto style = scrollArea->style( );
		int scrollBarWidth = style->pixelMetric( QStyle::PM_ScrollBarExtent, nullptr, scrollArea );
		newWidth += scrollBarWidth;
	}
	setFixedWidth( newWidth );
	optionListWidget->update( );
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

	setStyleSheet( R"(
QDockWidget {
    border: none;
}
/* 内容容器，消除内部暗线 */
QDockWidget > QWidget {
    border: none;
}
/* 标题栏不要额外边框 */
QDockWidget::title {
    border: none;
}
)" );

	scrollArea->setWidget( optionListWidget );
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	auto mainLayout = layout( );

	if( mainLayout ) {
		mainLayout->setContentsMargins( 0, 0, 0, 0 );
		mainLayout->setSpacing( 0 );
	}
	setWidget( scrollArea );
	setTitleBarWidget( dockTitleWidget );
	setContextMenuPolicy( Qt::PreventContextMenu );
	setFeatures( QDockWidget::NoDockWidgetFeatures );
	setAllowedAreas( Qt::LeftDockWidgetArea );
	setFloating( false );
	optionWindow->addDockWidget( Qt::LeftDockWidgetArea, this );
	show( );
	return true;
}
