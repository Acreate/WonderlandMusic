#ifndef MAINWINDOWJSONKEY_H_H_HEAD__FILE__
#define MAINWINDOWJSONKEY_H_H_HEAD__FILE__

#include "iJsonKey.h"

class MainWindowJsonKey : public IJsonKey {
	QString settingJsonPath;
	QString pointXPos;
	QString pointYPos;
	QString sizeWidth;
	QString sizeHeight;

public:
	bool init( ) override;

	virtual const QString & getSettingJsonPath( ) const;

	virtual const QString & getPointXPos( ) const;

	virtual const QString & getPointYPos( ) const;

	virtual const QString & getSizeWidth( ) const;

	virtual const QString & getSizeHeight( ) const;
};

#endif // MAINWINDOWJSONKEY_H_H_HEAD__FILE__
