#ifndef PLAYERWINDOWJSONKEY_H_H_HEAD__FILE__
#define PLAYERWINDOWJSONKEY_H_H_HEAD__FILE__

#include "iJsonKey.h"

class PlayerWindowJsonKey : public IJsonKey {
	QString playerWindowSettingJsonPath;
	QString playerWindowFileSelectWorkPath;
	QString playerWindowDirSelectWorkPath;

public:
	bool init( ) override;

	virtual const QString & getPlayerWindowSettingJsonPath( ) const;

	virtual const QString & getPlayerWindowFileSelectWorkPath( ) const;

	virtual const QString & getPlayerWindowDirSelectWorkPath( ) const;
};
#endif // PLAYERWINDOWJSONKEY_H_H_HEAD__FILE__
