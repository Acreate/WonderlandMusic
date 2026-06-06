#include "coreStackedWidget.h"

#include "../coreWindow.h"

#include <macro/widgetMarcoDefine.h>

#include "coreWidget/musicListWindow.h"
#include "coreWidget/settingWindow.h"

CoreStackedWidget::CoreStackedWidget( CoreWindow *parent ) : QStackedWidget( parent ), coreWindow( parent ) {
	musicListWindow = new MusicListWindow( this );
	musicListWindow->setWindowFlags( Qt::WindowType::Widget );
	addWidget( musicListWindow );

	settingWindow = new SettingWindow( this );
	settingWindow->setWindowFlags( Qt::WindowType::Widget );
	addWidget( settingWindow );
}
bool CoreStackedWidget::showMusicWidget( ) {

	Stack_Widget_Show_Widget( this, musicListWindow );
}
bool CoreStackedWidget::showSettingWidget( ) {
	Stack_Widget_Show_Widget( this, settingWindow );
}
size_t CoreStackedWidget::triggerSettingWindowEvent( SettingWindow *sender, const SettingWindowEventInfo &info ) {
	return 0;
}
