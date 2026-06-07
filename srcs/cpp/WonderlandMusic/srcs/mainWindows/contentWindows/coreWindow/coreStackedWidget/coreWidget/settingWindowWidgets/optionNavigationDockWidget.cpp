#include "optionNavigationDockWidget.h"

#include <QPushButton>

#include "../settingWindow.h"

#include "optionNavigationDockWidget/optionNavigationWidget.h"
OptionNavigationDockWidget::OptionNavigationDockWidget( SettingWindow *parent ) : QDockWidget( parent ), settingWindow( parent ) {
	optionNavigationWidget = new OptionNavigationWidget( this );
	setWidget( optionNavigationWidget );
}
