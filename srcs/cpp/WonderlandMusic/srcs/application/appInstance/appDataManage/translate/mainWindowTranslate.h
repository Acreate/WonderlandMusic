#ifndef MAINWINDOWTRANSLATE_H_H_HEAD__FILE__
#define MAINWINDOWTRANSLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class MainWindowTranslate : public ITranslate {
	QString appWindowTitleName;

public:
	bool init( ) override;

	virtual const QString & getAppWindowTitleName( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( MainWindow );
}
#endif // MAINWINDOWTRANSLATE_H_H_HEAD__FILE__
