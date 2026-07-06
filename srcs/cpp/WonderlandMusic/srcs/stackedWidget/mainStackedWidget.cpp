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
	disconnect( );
	return true;
}

bool MainStackedWidget::init( ) {
	Before_Init_Resource_App_Core_Ptr( playerWindow );
	Before_Init_Resource_App_Core_Ptr( settingWidget );

	Init_Resource_App_Core_Ptr( playerWindow );
	Init_Resource_App_Core_Ptr( settingWidget );
	Init_Resource_App_Core_Ptr( aboutWidget );

	After_Init_Resource_App_Core_Ptr( playerWindow );
	After_Init_Resource_App_Core_Ptr( settingWidget );

	return true;
}

bool MainStackedWidget::initBefore( ) {
	deleteResource( );
	playerWindow = new PlayerWindow( this );
	settingWidget = new SettingWidget( this );
	aboutWidget = new AboutWidget( this );
	return true;
}

bool MainStackedWidget::initAfter( ) {
	addWidget( playerWindow );
	addWidget( settingWidget );
	addWidget( aboutWidget );

	setCurrentIndex( 0 );
	return true;
}

bool MainStackedWidget::getJsonData( QJsonObject &get_json_object ) const {
	playerWindow->getJsonData( get_json_object );
	settingWidget->getJsonData( get_json_object );
	return true;
}

bool MainStackedWidget::setJsonData( const QJsonObject &set_json_object ) {
	playerWindow->setJsonData( set_json_object );
	settingWidget->setJsonData( set_json_object );
	return true;
}

PlayerWindow * MainStackedWidget::getPlayerWindow( ) const {
	return playerWindow;
}

SettingWidget * MainStackedWidget::getSettingWidget( ) const {
	return settingWidget;
}

AboutWidget * MainStackedWidget::getAboutWidget( ) const {
	return aboutWidget;
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
