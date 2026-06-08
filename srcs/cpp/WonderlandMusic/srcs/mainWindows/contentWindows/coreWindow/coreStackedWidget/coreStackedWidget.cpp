#include "coreStackedWidget.h"

#include "../coreWindow.h"

#include "../../../../applications/applicationInstance.h"
#include "../../../../applications/applicationEvenTrigger.h"

#include "../../../dockWidgets/functionWidget/functionWidget.h"

#include "coreWidget/musicListWindow.h"
#include "coreWidget/settingWindow.h"

CoreStackedWidget::CoreStackedWidget( CoreWindow *parent ) : BaseStackedWidget( parent ), coreWindow( parent ) {

	musicListWindow = new MusicListWindow( this );
	musicListWindow->setWindowFlags( Qt::WindowType::Widget );
	addWidget( musicListWindow );

	settingWindow = new SettingWindow( this );
	settingWindow->setWindowFlags( Qt::WindowType::Widget );
	addWidget( settingWindow );
	
	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerFunctionWidgetEvent, [this] ( auto, const FunctionWidgetEventInfo &info ) {
		auto eventType = info.getEventType( );
		switch( eventType ) {
			case FunctionWidgetEventInfo::EventType::None :
				break;
			case FunctionWidgetEventInfo::EventType::Show_Music :
				setCurrentWidget( musicListWindow );
				break;
			case FunctionWidgetEventInfo::EventType::Show_Setting :
				setCurrentWidget( settingWindow );
				break;
		}
	} );

}
