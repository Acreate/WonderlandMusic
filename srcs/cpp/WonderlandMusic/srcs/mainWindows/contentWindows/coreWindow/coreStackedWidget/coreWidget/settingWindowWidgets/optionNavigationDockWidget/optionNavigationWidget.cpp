#include "optionNavigationWidget.h"

#include <QPushButton>

#include "../optionNavigationDockWidget.h"

#include <applications/applicationEvenTrigger.h>

#include "../../../../../../../applications/application.h"

OptionNavigationWidget::OptionNavigationWidget( OptionNavigationDockWidget *parent ) : QWidget( parent ), optionNavigationDockWidget( parent ) {

	pathBtn = new QPushButton( tr( "路径" ), this );
	aboutBtn = new QPushButton( tr( "关于" ), this );
	connect( pathBtn, &QPushButton::clicked, [this]( ) {
		OptionNavigationWidgetEvent::triggerOptionNavigationWidgetEvent( Application::getApplicationInstance( )->getApplicationEvenTrigger( ), this, OptionNavigationWidgetEventInfo( OptionNavigationWidgetEventInfo::EventType::Show_Path_Widget ) );
	} );
	connect( aboutBtn, &QPushButton::clicked, [this]( ) {
		OptionNavigationWidgetEvent::triggerOptionNavigationWidgetEvent( Application::getApplicationInstance( )->getApplicationEvenTrigger( ), this, OptionNavigationWidgetEventInfo( OptionNavigationWidgetEventInfo::EventType::Show_About_Widget ) );
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
