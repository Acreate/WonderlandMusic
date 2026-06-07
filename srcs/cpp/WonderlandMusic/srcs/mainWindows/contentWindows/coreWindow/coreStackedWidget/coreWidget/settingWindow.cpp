#include "settingWindow.h"

#include "../coreStackedWidget.h"


#include "../../../../../applications/application.h"

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
