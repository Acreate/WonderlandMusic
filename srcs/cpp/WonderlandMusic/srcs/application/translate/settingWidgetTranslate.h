#ifndef SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
#define SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class SettingWidgetTranslate : public ITranslate {
	QString okBtnTxt;
	QString cancelBtnTxt;
	QString selectFileBtnTxt;
	QString selectDirBtnTxt;
	QString selectDirLinePlaceholderTxt;
	QString setectPathGroupTitle;
public:
	bool init( ) override;

	virtual const QString & getOkBtnTxt( ) const;

	virtual const QString & getCancelBtnTxt( ) const;

	virtual const QString & getSelectFileBtnTxt( ) const;

	virtual const QString & getSelectDirBtnTxt( ) const;

	virtual const QString & getSelectDirLinePlaceholderTxt( ) const;

	virtual const QString & getSetectPathGroupTitle( ) const;
};

#endif // SETTINGWIDGETTRANSLATE_H_H_HEAD__FILE__
