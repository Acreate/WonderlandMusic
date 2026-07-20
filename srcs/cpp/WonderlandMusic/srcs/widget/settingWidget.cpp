#include "settingWidget.h"
#include "../application/translate/settingWidgetTranslate.h"
#include "../component/optionWindow/optionWindow.h"
#include "../tools/appTranslateTools.h"

SettingWidget::SettingWidget( OptionWindow *parent ) : QWidget( parent ), OptionPanel( parent ) {
}

SettingWidget::~SettingWidget( ) {
	deleteResource( );
}

void SettingWidget::response( ) {
}

QWidget * SettingWidget::toWidget( ) {
	return this;
}

bool SettingWidget::deleteResource( ) {
	return true;
}

bool SettingWidget::initBefore( ) {
	if( AppTranslateTools::getSettingWidget( [this] ( SettingWidgetTranslate &translate ) {
		setName( translate.getTitleName( ) );
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
