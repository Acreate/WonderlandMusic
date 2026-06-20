#include "settingWidget.h"

SettingWidget::SettingWidget( QWidget *parent ) : QWidget( parent ) {
}

bool SettingWidget::loadJsonPathInfo( ) {
	return true;
}

bool SettingWidget::writeJsonPathInfo( ) {
	return false;
}

bool SettingWidget::init( ) {
	if( loadJsonPathInfo( ) == false )
		return false;
	return true;
}

void SettingWidget::hideEvent( QHideEvent *event ) {
	writeJsonPathInfo( );
	QWidget::hideEvent( event );
}
