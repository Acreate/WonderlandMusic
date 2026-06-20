#ifndef MAINWINDOWJSONKEY_H_H_HEAD__FILE__
#define MAINWINDOWJSONKEY_H_H_HEAD__FILE__


#include "iJsonKey.h"

class MainWindowJsonKey : public IJsonKey {
	QString mainWindowSettingJsonPath;
	QString mainWindowPointXPos;
	QString mainWindowPointYPos;
	QString mainWindowSizeWidth;
	QString mainWindowSizeHeight;

public:
	bool init( ) override;

	virtual const QString & getMainWindowSettingJsonPath( ) const;

	virtual const QString & getMainWindowPointXPos( ) const;

	virtual const QString & getMainWindowPointYPos( ) const;

	virtual const QString & getMainWindowSizeWidth( ) const;

	virtual const QString & getMainWindowSizeHeight( ) const;
};


#endif // MAINWINDOWJSONKEY_H_H_HEAD__FILE__
