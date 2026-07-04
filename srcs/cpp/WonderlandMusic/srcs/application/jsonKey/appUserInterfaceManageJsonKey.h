#ifndef APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class AppUserInterfaceManageJsonKey : public IJsonKey {
	QString mainWindow;
	QString filePath;

public:
	bool init( ) override;

	virtual const QString & getMainWindow( ) const;

	virtual QString getFilePath( ) const;
};

#endif // APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
