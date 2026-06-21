#ifndef PLAYERLISTMENUJSONKEY_H_H_HEAD__FILE__
#define PLAYERLISTMENUJSONKEY_H_H_HEAD__FILE__
#include "iJsonKey.h"

class PlayerListMenuJsonKey : public IJsonKey {
	QString settingJsonPath;
	QString fileSelectWorkPath;
	QString dirSelectWorkPath;
public:
	bool init( ) override;

	virtual const QString & getSettingJsonPath( ) const;

	virtual const QString & getFileSelectWorkPath( ) const;

	virtual const QString & getDirSelectWorkPath( ) const;
};

#endif // PLAYERLISTMENUJSONKEY_H_H_HEAD__FILE__
