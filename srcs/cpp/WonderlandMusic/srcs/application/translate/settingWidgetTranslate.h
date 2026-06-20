#ifndef SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
#define SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class SettingWidgetTranslate : public ITranslate {
public:
	bool init( ) override;
};

class AboutWidgetTranslate : public ITranslate {
public:
	bool init( ) override;
};

#endif // SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
