#ifndef APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
#include <interface/iJsonKey.h>

class AppUserInterfaceManageJsonKey : public IJsonKey {
	QString mainWindow;
	QString musicListTopWidget;
	QString musicFavoriteWidget;

public:
	bool init( ) override;

	virtual const QString & getMainWindow( ) const;

	virtual const QString & getMusicListTopWidget( ) const;

	virtual const QString & getMusicFavoriteWidget( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( AppUserInterfaceManage );
}

#endif // APPUSERINTERFACEMANAGEJSONKEY_H_H_HEAD__FILE__
