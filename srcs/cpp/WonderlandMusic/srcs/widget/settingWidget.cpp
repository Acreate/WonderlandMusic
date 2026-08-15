#include "settingWidget.h"

#include "../application/appInstance/appDataManage/translate/settingWidgetTranslate.h"

#include "../component/optionWindow/optionWindow.h"

SettingWidget::SettingWidget( OptionWindow *parent ) : QWidget( parent ), OptionPanel( ) {
}

SettingWidget::~SettingWidget( ) {
}

QWidget * SettingWidget::toWidget( ) {
	return this;
}
bool SettingWidget::showPanelBefore( ) {
	return true;
}
bool SettingWidget::hidePanelBefore( ) {
	return true;
}
bool SettingWidget::releasePanelBefore( ) {
	return true;
}
const char * SettingWidget::getTypeName( ) const {
	return metaObject( )->className( );
}

bool SettingWidget::deleteResource( ) {
	return true;
}

bool SettingWidget::initBefore( ) {
	if( AppTranslateTools::getSettingWidget( [this] ( SettingWidgetTranslate &translate ) {
		setName( translate.getTitleName( ) );
		return true;
	} ) == false )
		setName( tr( "设置" ) );
	return true;
}

bool SettingWidget::init( ) {
	return true;
}

bool SettingWidget::initAfter( ) {
	return true;
}
