#ifndef SYSTEMTRAYICONTRANSLATE_H_H_HEAD__FILE__
#define SYSTEMTRAYICONTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class SystemTrayIconTranslate : public ITranslate{
	QString isSystemTrayAvailableError;
	QString iconFileNotExists;
	QString iconLoadFileError;
	QString appName;
public:
	bool init( ) override;

	virtual const QString & getIsSystemTrayAvailableError( ) const;

	virtual const QString & getIconFileNotExists( ) const;

	virtual const QString & getIconLoadFileError( ) const;

	virtual const QString & getAppName( ) const;
};

#endif // SYSTEMTRAYICONTRANSLATE_H_H_HEAD__FILE__
