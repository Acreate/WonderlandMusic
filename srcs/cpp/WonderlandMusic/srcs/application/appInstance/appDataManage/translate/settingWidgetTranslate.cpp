#include "settingWidgetTranslate.h"

bool SettingWidgetTranslate::init( ) {
	titleName = QObject::tr( "设置" );
	return true;
}

const QString & SettingWidgetTranslate::getTitleName( ) const {
	return titleName;
}
