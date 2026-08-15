#ifndef SYSTEMTRAYICONTRANSLATE_H_H_HEAD__FILE__
#define SYSTEMTRAYICONTRANSLATE_H_H_HEAD__FILE__

#include <interface/iTranslate.h>

class SystemTrayIconTranslate : public ITranslate {
	QString isSystemTrayAvailableError;
	QString iconFileNotExists;
	QString iconLoadFileError;
	QString appName;

public:
	bool init( ) override;

public:
	virtual const QString & getIsSystemTrayAvailableError( ) const;

	virtual const QString & getIconFileNotExists( ) const;

	virtual const QString & getIconLoadFileError( ) const;

	virtual const QString & getAppName( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( SystemTrayIcon );
}
#endif // SYSTEMTRAYICONTRANSLATE_H_H_HEAD__FILE__
