#ifndef SYSTEMTRAYICONMENUTRANSLATE_H_H_HEAD__FILE__
#define SYSTEMTRAYICONMENUTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class SystemTrayIconMenuTranslate : public ITranslate{
	QString showMainMenu;
	QString quitApp;
public:
	bool init( ) override;

	virtual const QString & getShowMainMenu( ) const;

	virtual const QString & getQuitApp( ) const;
};

#endif // SYSTEMTRAYICONMENUTRANSLATE_H_H_HEAD__FILE__
