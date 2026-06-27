#ifndef APPINSTANCEJSONKEY_H_H_HEAD__FILE__
#define APPINSTANCEJSONKEY_H_H_HEAD__FILE__
#include "iJsonKey.h"

class AppInstanceJsonKey : public IJsonKey{
	QString appIniHomeDirPath;

public:
	bool init( ) override;

	virtual const QString & getAppIniHomeDirPath( ) const;
};

#endif // APPINSTANCEJSONKEY_H_H_HEAD__FILE__
