#include "settingWindow.h"

#include "../coreStackedWidget.h"

#include <applications/applicationEvenTrigger.h>

#include "../../../../../applications/application.h"

#include "settingWindowWidgets/optionNavigationDockWidget.h"
#include "settingWindowWidgets/optionStackWidget.h"
#include "settingWindowWidgets/optionNavigationDockWidget/optionNavigationBarWidget.h"
#include "settingWindowWidgets/optionNavigationDockWidget/optionNavigationWidget.h"
SettingWindow::SettingWindow( CoreStackedWidget *parent ) : QMainWindow( parent ), coreStackedWidget( parent ) {
	optionStackWidget = new OptionStackWidget( this );
	setCentralWidget( optionStackWidget );

	optionNavigationDockWidget = new OptionNavigationDockWidget( this );
	optionNavigationDockWidget->setAllowedAreas( Qt::LeftDockWidgetArea );
	optionNavigationDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	optionNavigationDockWidget->setContextMenuPolicy( Qt::NoContextMenu );
	optionNavigationDockWidget->setTitleBarWidget( new OptionNavigationBarWidget( optionNavigationDockWidget ) );
	addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, optionNavigationDockWidget );

	Application *applicationInstance = Application::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	// 绑定导航
	connect( applicationEvenTrigger, &ApplicationEvenTrigger::triggerOptionNavigationWidgetEvent, [this] ( OptionNavigationWidget *, const OptionNavigationWidgetEventInfo &info ) {
		switch( info.getEventType( ) ) {
			case OptionNavigationWidgetEventInfo::EventType::None :
				break;
			case OptionNavigationWidgetEventInfo::EventType::Show_Path_Widget :
				optionStackWidget->showPathSettingWidget( );
				break;
			case OptionNavigationWidgetEventInfo::EventType::Show_About_Widget :
				optionStackWidget->showAboutInfoWidget( );
				break;
		}
	} );
}
