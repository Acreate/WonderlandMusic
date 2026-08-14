#ifndef APPMUSICMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPMUSICMANAGEJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class AppMusicManageJsonKey : public IJsonKey {
	QString jsonObejct;
	QString selectFilePath;
	QString selectDirPath;
	QString musicCentreWidgetKey;

public:
	bool init( ) override;

	virtual const QString & getJsonObejct( ) const;

	virtual const QString & getSelectFilePath( ) const;

	virtual const QString & getSelectDirPath( ) const;
	virtual const QString & getMusicCentreWidgetKey( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( AppMusicManage );
}

#endif // APPMUSICMANAGEJSONKEY_H_H_HEAD__FILE__
