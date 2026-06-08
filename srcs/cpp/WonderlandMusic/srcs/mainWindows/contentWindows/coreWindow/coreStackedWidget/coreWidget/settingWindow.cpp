#include "settingWindow.h"

#include "../coreStackedWidget.h"

#include "../../../../../applications/applicationInstance.h"

#include "settingWindowWidgets/optionNavigationDockWidget.h"
#include "settingWindowWidgets/optionStackWidget.h"
SettingWindow::SettingWindow( CoreStackedWidget *parent ) : BaseMainWindow( parent ), coreStackedWidget( parent ) {
	optionStackWidget = new OptionStackWidget( this );
	setCentralWidget( optionStackWidget );
	optionNavigationDockWidget = new OptionNavigationDockWidget( this );
	optionNavigationDockWidget->setAllowedAreas( Qt::LeftDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, optionNavigationDockWidget );
}
