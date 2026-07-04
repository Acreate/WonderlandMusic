#ifndef APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class AppDataManageJsonKey : public IJsonKey {
	QString jsonFilePath;
	QString appMusicManage;
	QString iniDirHomePath;

public:
	bool init( ) override;

	virtual const QString & getJsonFilePath( ) const;

	virtual const QString & getAppMusicManage( ) const;

	virtual const QString & getIniDirHomePath( ) const;
};

#endif // APPDATAMANAGEJSONKEY_H_H_HEAD__FILE__
