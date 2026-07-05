#ifndef APPINSTANCE_H_H_HEAD__FILE__
#define APPINSTANCE_H_H_HEAD__FILE__

#include <QApplication>

#include "../interface/iAppCore.h"

class AppMenuManage;
class AppDateTimerManage;
class AppUserInterfaceManage;
class AppDataManage;

class AppInstance : public QApplication, public IAppCore {
	Q_OBJECT;

private:
	static AppInstance *instance;

protected:
	/// @brief 数据管理
	AppDataManage *appDataManage = nullptr;
	/// @brief 用户界面
	AppUserInterfaceManage *appUserInterfaceManage = nullptr;
	/// @brief 时间管理
	AppDateTimerManage *appDateTimerManage = nullptr;
	/// @brief 菜单管理
	AppMenuManage *appMenuManage = nullptr;

public:
	static AppInstance * getAppInstance( );

	AppInstance( int &argc, char **argv, int app_flag_s = ApplicationFlags );

	~AppInstance( ) override;

	bool notify( QObject *, QEvent * ) override;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

protected:
	bool deleteResource( ) override;

public:
	virtual AppDataManage * getAppDataManage( ) const;

	virtual AppUserInterfaceManage * getAppUserInterfaceManage( ) const;

	virtual AppDateTimerManage * getAppDateTimerManage( ) const;
};
#endif // APPINSTANCE_H_H_HEAD__FILE__
