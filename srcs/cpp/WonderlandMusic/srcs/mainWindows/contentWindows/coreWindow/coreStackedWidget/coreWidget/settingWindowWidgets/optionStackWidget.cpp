#include "optionStackWidget.h"

#include "../settingWindow.h"

#include "../../../../../../applications/applicationInstance.h"
#include "../../../../../../applications/applicationEvenTrigger.h"

#include "../../../../../../msgInfo/messageErrorOut.h"

#include "optionNavigationDockWidget/optionNavigationWidget.h"

#include "optionWidget/aboutApplicationWidget.h"
#include "optionWidget/pathSettingWidget.h"

OptionStackWidget::OptionStackWidget( SettingWindow *parent ) : BaseStackedWidget( parent ), settingWindow( parent ) {
	pathSettingWidget = new PathSettingWidget( this );
	addWidget( pathSettingWidget );
	aboutApplicationWidget = new AboutApplicationWidget( this );
	addWidget( aboutApplicationWidget );

	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );

	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerOptionNavigationWidgetEvent, [this] ( auto, const OptionNavigationWidgetEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {

			case OptionNavigationWidgetEventInfo::EventType::None :
				break;
			case OptionNavigationWidgetEventInfo::EventType::Show_Path_Widget :
				setCurrentWidget( pathSettingWidget );
				break;
			case OptionNavigationWidgetEventInfo::EventType::Show_About_Widget :
				setCurrentWidget( aboutApplicationWidget );
				break;
		}
	} );
}
