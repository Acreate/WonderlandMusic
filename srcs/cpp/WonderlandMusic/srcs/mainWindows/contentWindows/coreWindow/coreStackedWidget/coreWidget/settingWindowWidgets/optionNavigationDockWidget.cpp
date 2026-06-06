#include "optionNavigationDockWidget.h"

#include <QPushButton>

#include "../settingWindow.h"

#include "optionNavigationDockWidget/optionNavigationWidget.h"
OptionNavigationDockWidget::OptionNavigationDockWidget( SettingWindow *parent ) : QDockWidget( parent ), settingWindow( parent ) {
	optionNavigationWidget = new OptionNavigationWidget( this );
	setWidget( optionNavigationWidget );
}
size_t OptionNavigationDockWidget::triggerOptionNavigationWidgetEvent( OptionNavigationWidget *sender, const OptionNavigationWidgetEventInfo &info ) {
	auto eventType = info.getEventType( );
	switch( eventType ) {

		case OptionNavigationWidgetEventInfo::EventType::None :
			break;
		case OptionNavigationWidgetEventInfo::EventType::Show_Path_Widget :
			return OptionNavigationDockWidgetEvent::triggerOptionNavigationDockWidgetEvent( settingWindow, this, OptionNavigationDockWidgetEventInfo( OptionNavigationDockWidgetEventInfo::EventType::Show_Path_Widget ) );
			break;
		case OptionNavigationWidgetEventInfo::EventType::Show_About_Widget :
			return OptionNavigationDockWidgetEvent::triggerOptionNavigationDockWidgetEvent( settingWindow, this, OptionNavigationDockWidgetEventInfo( OptionNavigationDockWidgetEventInfo::EventType::Show_About_Widget ) );
			break;
	}
	return 0;
}
