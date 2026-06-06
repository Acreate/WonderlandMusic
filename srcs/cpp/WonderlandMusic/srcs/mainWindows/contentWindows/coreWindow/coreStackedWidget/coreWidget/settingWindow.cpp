#include "settingWindow.h"

#include "../coreStackedWidget.h"

#include "settingWindowWidgets/optionNavigationDockWidget.h"
#include "settingWindowWidgets/optionStackWidget.h"
#include "settingWindowWidgets/optionNavigationDockWidget/optionNavigationBarWidget.h"
SettingWindow::SettingWindow( CoreStackedWidget *parent ) : QMainWindow( parent ), coreStackedWidget( parent ) {
	optionStackWidget = new OptionStackWidget( this );
	setCentralWidget( optionStackWidget );

	optionNavigationDockWidget = new OptionNavigationDockWidget( this );
	optionNavigationDockWidget->setAllowedAreas( Qt::LeftDockWidgetArea );
	optionNavigationDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	optionNavigationDockWidget->setContextMenuPolicy( Qt::NoContextMenu );
	optionNavigationDockWidget->setTitleBarWidget( new OptionNavigationBarWidget( optionNavigationDockWidget ) );
	addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, optionNavigationDockWidget );
}
size_t SettingWindow::triggerOptionNavigationDockWidgetEvent( OptionNavigationDockWidget *sender, const OptionNavigationDockWidgetEventInfo &info ) {
	auto eventType = info.getEventType( );
	switch( eventType ) {

		case OptionNavigationDockWidgetEventInfo::EventType::None :
			break;
		case OptionNavigationDockWidgetEventInfo::EventType::Show_Path_Widget :
			optionStackWidget->showPathSettingWidget( );
			break;
		case OptionNavigationDockWidgetEventInfo::EventType::Show_About_Widget :
			optionStackWidget->showAboutInfoWidget( );
			break;
	}
	return 0;
}
