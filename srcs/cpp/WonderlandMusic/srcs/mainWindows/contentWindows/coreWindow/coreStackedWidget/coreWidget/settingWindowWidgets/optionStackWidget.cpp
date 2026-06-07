#include "optionStackWidget.h"

#include "../settingWindow.h"

#include <macro/widgetMarcoDefine.h>

#include "../../../../../../msgInfo/messageErrorOut.h"

#include "optionWidget/aboutApplicationWidget.h"
#include "optionWidget/pathSettingWidget.h"

OptionStackWidget::OptionStackWidget( SettingWindow *parent ) : QStackedWidget( parent ), settingWindow( parent ) {
	pathSettingWidget = new PathSettingWidget( this );
	addWidget( pathSettingWidget );
	aboutApplicationWidget = new AboutApplicationWidget( this );
	addWidget( aboutApplicationWidget );
}
bool OptionStackWidget::showAboutInfoWidget( ) {
	Stack_Widget_Show_Widget( this, aboutApplicationWidget );
}
bool OptionStackWidget::showPathSettingWidget( ) {
	Stack_Widget_Show_Widget( this, pathSettingWidget );
}
