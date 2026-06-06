#include "coreStackedWidget.h"

#include "../coreWindow.h"

#include "coreWidget/musicListWindow.h"
#include "coreWidget/settingWindow.h"

#define Show_Stack_Sub_Widget( show_widget ) \
	if( currentWidget( ) == show_widget ) \
		return true; \
	setCurrentWidget( show_widget ); \
	if( currentWidget( ) == show_widget ) \
		return true;\
	return false

CoreStackedWidget::CoreStackedWidget( CoreWindow *parent ) : QStackedWidget( parent ), coreWindow( parent ) {
	musicListWindow = new MusicListWindow( this );
	musicListWindow->setWindowFlags( Qt::WindowType::Widget );
	addWidget( musicListWindow );

	settingWindow = new SettingWindow( this );
	settingWindow->setWindowFlags( Qt::WindowType::Widget );
	addWidget( settingWindow );
}
bool CoreStackedWidget::showMusicWidget( ) {
	Show_Stack_Sub_Widget( musicListWindow );

}
bool CoreStackedWidget::showSettingWidget( ) {
	Show_Stack_Sub_Widget( settingWindow );
}
