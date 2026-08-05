#include "settingWidgetTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/appTranslateTools.h>

Defininition_Get_Translate( SettingWidget );

bool SettingWidgetTranslate::init( ) {
	titleName = QObject::tr( "设置" );
	return true;
}

const QString & SettingWidgetTranslate::getTitleName( ) const {
	return titleName;
}
