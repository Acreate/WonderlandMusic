#ifndef MAINWINDOWTRANSLATE_H_H_HEAD__FILE__
#define MAINWINDOWTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class MainWindowTranslate : public ITranslate {
	QString appWindowTitleName;

	QString settingWidget;

	QString aboutWidget;
	QString musicTypeName;

public:
	bool init( ) override;

	virtual const QString & getAppWindowTitleName( ) const;

	virtual const QString & getSettingWidget( ) const;

	virtual const QString & getAboutWidget( ) const;

	virtual const QString & getMusicTypeName( ) const;
};
#endif // MAINWINDOWTRANSLATE_H_H_HEAD__FILE__
