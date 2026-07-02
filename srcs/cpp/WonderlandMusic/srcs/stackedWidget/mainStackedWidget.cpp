#include "mainStackedWidget.h"

#include "../widget/aboutWidget.h"
#include "../widget/settingWidget.h"

#include "../window/playerWindow.h"

MainStackedWidget::MainStackedWidget( QWidget *parent ) : QStackedWidget( parent ) {
}

bool MainStackedWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( playerWindow );
	Delete_Resource_App_Core_Ptr( settingWidget );
	Delete_Resource_App_Core_Ptr( aboutWidget );
	return true;
}

bool MainStackedWidget::init( ) {
	deleteResource( );
	playerWindow = new PlayerWindow( this );
	settingWidget = new SettingWidget( this );
	aboutWidget = new AboutWidget( this );

	if( playerWindow->init( ) == false )
		return false;
	if( settingWidget->init( ) == false )
		return false;
	if( aboutWidget->init( ) == false )
		return false;

	addWidget( playerWindow );
	addWidget( settingWidget );
	addWidget( aboutWidget );

	return true;
}

void MainStackedWidget::slot_showPlayerWidget( ) {
	setCurrentWidget( playerWindow );
}

void MainStackedWidget::slot_showSettingWidget( ) {
	setCurrentWidget( settingWidget );
}

void MainStackedWidget::slot_showAboutWidget( ) {
	setCurrentWidget( aboutWidget );
}
