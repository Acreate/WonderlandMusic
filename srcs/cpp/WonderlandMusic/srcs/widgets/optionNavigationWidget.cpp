#include "optionNavigationWidget.h"

#include <QPushButton>


#include <applications/applicationEvenTrigger.h>

#include <applications/applicationInstance.h>

#include "../dockWidgets/optionNavigationDockWidget.h"

OptionNavigationWidget::OptionNavigationWidget( OptionNavigationDockWidget *parent ) : BaseWidget( parent ), optionNavigationDockWidget( parent ) {
	pathBtn = new QPushButton( tr( "路径" ), this );
	aboutBtn = new QPushButton( tr( "关于" ), this );
	connect( pathBtn, &QPushButton::clicked, [this]( ) {
		auto applicationInstance = ApplicationInstance::getApplicationInstance( );
		auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
		OptionNavigationWidgetEvent::triggerOptionNavigationWidgetEvent( applicationEvenTrigger, this, OptionNavigationWidgetEventInfo( OptionNavigationWidgetEventInfo::EventType::Show_Path_Widget ) );
	} );
	connect( aboutBtn, &QPushButton::clicked, [this]( ) {
		auto applicationInstance = ApplicationInstance::getApplicationInstance( );
		auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
		OptionNavigationWidgetEvent::triggerOptionNavigationWidgetEvent( applicationEvenTrigger, this, OptionNavigationWidgetEventInfo( OptionNavigationWidgetEventInfo::EventType::Show_About_Widget ) );
	} );
	pathBtn->move( 0, 0 );
	int height = pathBtn->height( );
	aboutBtn->move( 0, height );
	auto pathWidth = pathBtn->width( );
	auto aboutWidh = aboutBtn->width( );
	height += aboutBtn->height( );
	setFixedWidth( pathWidth > aboutWidh ? pathWidth : aboutWidh );
	setMinimumHeight( height );
}
