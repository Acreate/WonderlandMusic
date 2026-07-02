#ifndef OPTIONDOCKWIDGETTRANSLATE_H_H_HEAD__FILE__
#define OPTIONDOCKWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class OptionDockWidgetTranslate : public ITranslate {
	QString settingWidget;

	QString aboutWidget;
	QString musicTypeName;

public:
	bool init( ) override;

	virtual const QString & getSettingWidget( ) const;

	virtual const QString & getAboutWidget( ) const;

	virtual const QString & getMusicTypeName( ) const;
};

#endif // OPTIONDOCKWIDGETTRANSLATE_H_H_HEAD__FILE__
