#include "settingWidget.h"

#include <qboxlayout.h>

#include "selectDirPathWidget.h"

#include "../tools/autoMakePtrTools.h"

void SettingWidget::deleteResource( ) {
	#define d_r( ptr ) if(ptr ) (delete ptr, ptr = nullptr)
	d_r( appJsonPathWidget );
}

SettingWidget::SettingWidget( QWidget *parent ) : QWidget( parent ) {
}

bool SettingWidget::loadJsonPathInfo( ) {
	return true;
}

bool SettingWidget::writeJsonPathInfo( ) {
	return true;
}

bool SettingWidget::initWidget( ) {
	if( AutoMakePtrTools::makePtr( appJsonPathWidget, this ) == nullptr )
		return false;
	QVBoxLayout *vBoxLayout = new QVBoxLayout( this );

	vBoxLayout->addWidget( appJsonPathWidget );

	auto spacerItem = new QSpacerItem( 10, 10, QSizePolicy::Ignored, QSizePolicy::Expanding );
	vBoxLayout->addSpacerItem( spacerItem );
	return true;
}

bool SettingWidget::init( ) {
	deleteResource( );
	if( initWidget( ) == false )
		return false;

	if( loadJsonPathInfo( ) == false )
		return false;
	return true;
}

void SettingWidget::hideEvent( QHideEvent *event ) {
	writeJsonPathInfo( );
	QWidget::hideEvent( event );
}
