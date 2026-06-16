#include "optionNavigationDockWidget.h"

#include "../mainWindows/settingWindow.h"

#include "../widgets/optionNavigationWidget.h"

OptionNavigationDockWidget::OptionNavigationDockWidget( SettingWindow *parent ) : BaseDockWidget( parent ), settingWindow( parent ) {
	optionNavigationWidget = new OptionNavigationWidget( this );
	setWidget( optionNavigationWidget );
}
