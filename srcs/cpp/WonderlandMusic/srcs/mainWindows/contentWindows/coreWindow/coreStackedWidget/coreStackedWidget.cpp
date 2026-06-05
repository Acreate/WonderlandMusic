#include "coreStackedWidget.h"

#include "../coreWindow.h"

#include "coreWidget/musicListWindow.h"
#include "coreWidget/settingWindow.h"
CoreStackedWidget::CoreStackedWidget( CoreWindow *parent ) : QStackedWidget( parent ), coreWindow( parent ) {
	musicListWindow = new MusicListWindow( this );
	musicListWindow->setWindowFlags( Qt::WindowType::Widget );
	addWidget( musicListWindow );

	settingWindow = new SettingWindow( this );
	setWindowFlags( Qt::WindowType::Widget );
	addWidget( settingWindow );
}
