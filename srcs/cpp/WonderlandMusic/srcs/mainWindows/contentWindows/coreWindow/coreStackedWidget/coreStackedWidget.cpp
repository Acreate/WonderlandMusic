#include "coreStackedWidget.h"

#include "../coreWindow.h"

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
	if( currentWidget( ) == musicListWindow )
		return true;
	setCurrentWidget( musicListWindow );
	if( currentWidget( ) == musicListWindow )
		return true;
	return false;
}
bool CoreStackedWidget::showSettingWidget( ) {
	if( currentWidget( ) == settingWindow )
		return true;
	setCurrentWidget( settingWindow );
	if( currentWidget( ) == settingWindow )
		return true;
	return false;
}
