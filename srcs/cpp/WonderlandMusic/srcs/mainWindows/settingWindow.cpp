#include "settingWindow.h"

#include "../dockWidgets/optionNavigationDockWidget.h"

#include "../stackedWidgets/coreStackedWidget.h"
#include "../stackedWidgets/optionStackWidget.h"

SettingWindow::SettingWindow( CoreStackedWidget *parent ) : BaseMainWindow( parent ), coreStackedWidget( parent ) {
	
	optionStackWidget = new OptionStackWidget( this );
	setCentralWidget( optionStackWidget );
	optionNavigationDockWidget = new OptionNavigationDockWidget( this );
	optionNavigationDockWidget->setAllowedAreas( Qt::LeftDockWidgetArea );
	addDockWidget( Qt::DockWidgetArea::LeftDockWidgetArea, optionNavigationDockWidget );
}
