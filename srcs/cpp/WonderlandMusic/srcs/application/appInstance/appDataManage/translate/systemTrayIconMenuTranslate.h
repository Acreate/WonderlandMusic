#ifndef SYSTEMTRAYICONMENUTRANSLATE_H_H_HEAD__FILE__
#define SYSTEMTRAYICONMENUTRANSLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class SystemTrayIconMenuTranslate : public ITranslate {
	QString showMainMenu;
	QString quitApp;

public:
	bool init( ) override;

public:
	virtual const QString & getShowMainMenu( ) const;

	virtual const QString & getQuitApp( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( SystemTrayIconMenu );
}
#endif // SYSTEMTRAYICONMENUTRANSLATE_H_H_HEAD__FILE__
