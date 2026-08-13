#include "settingWidget.h"
#include "../application/translate/settingWidgetTranslate.h"
#include "../component/optionWindow/optionWindow.h"

SettingWidget::SettingWidget( OptionWindow *parent ) : QWidget( parent ), OptionPanel( ) {
}

SettingWidget::~SettingWidget( ) {
}

QWidget * SettingWidget::toWidget( ) {
	return this;
}
bool SettingWidget::readJsonData( ) {
	return true;
}
bool SettingWidget::writeJsonData( ) {
	return true;
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

bool SettingWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool SettingWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
