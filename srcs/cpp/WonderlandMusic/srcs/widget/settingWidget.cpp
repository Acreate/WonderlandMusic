#include "settingWidget.h"

#include "../application/appInstance/appDataManage/translate/settingWidgetTranslate.h"

#include "../component/optionWindow/optionWindow.h"

#include "../head/result_message_out.h"

SettingWidget::SettingWidget( ) : QWidget( ), OptionPanel( ) {
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
QString SettingWidget::getTypeName( ) const {
	return metaObject( )->className( );
}

bool SettingWidget::deleteResource( ) {
	return true;
}

bool SettingWidget::initBefore( ) {
	return true;
}

bool SettingWidget::init( ) {
	if( AppTranslateTools::getSettingWidget( [this] ( SettingWidgetTranslate &translate ) {
		setName( translate.getTitleName( ) );
		return true;
	} ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, this, init(), tr( "无法获取翻译实例" ) );
	return true;
}

bool SettingWidget::initAfter( ) {
	return true;
}
