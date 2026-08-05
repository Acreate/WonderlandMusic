#ifndef SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
#define SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class SettingWidgetTranslate : public ITranslate {
	QString titleName;

public:
	bool init( ) override;

	virtual const QString & getTitleName( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( SettingWidget );
}
#endif // SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
