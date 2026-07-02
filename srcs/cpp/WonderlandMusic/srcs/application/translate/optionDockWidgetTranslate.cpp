#include "optionDockWidgetTranslate.h"

bool OptionDockWidgetTranslate::init( ) {
	musicTypeName = QObject::tr( "音频" );
	settingWidget = QObject::tr( "软件设置" );
	aboutWidget = QObject::tr( "关于" );
	return true;
}

const QString & OptionDockWidgetTranslate::getSettingWidget( ) const {
	return settingWidget;
}

const QString & OptionDockWidgetTranslate::getAboutWidget( ) const {
	return aboutWidget;
}

const QString & OptionDockWidgetTranslate::getMusicTypeName( ) const {
	return musicTypeName;
}
