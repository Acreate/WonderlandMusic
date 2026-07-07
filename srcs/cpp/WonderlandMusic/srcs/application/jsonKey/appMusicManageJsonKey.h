#ifndef APPMUSICMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPMUSICMANAGEJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class AppMusicManageJsonKey : public IJsonKey {
	QString jsonObejct;
	QString filePath;
	QString selectFilePath;
	QString selectDirPath;

public:
	bool init( ) override;

	virtual const QString & getJsonObejct( ) const;
	virtual QString getFilePath( ) const;

	virtual const QString & getSelectFilePath( ) const;

	virtual const QString & getSelectDirPath( ) const;
};

#endif // APPMUSICMANAGEJSONKEY_H_H_HEAD__FILE__
