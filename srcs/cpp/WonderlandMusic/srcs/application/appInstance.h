#ifndef APPINSTANCE_H_H_HEAD__FILE__
#define APPINSTANCE_H_H_HEAD__FILE__

#include <QApplication>

#include "../interface/iAppCore.h"
#include "../interface/iAppResourceCore.h"

class ApplicationManage;
class AppDateTimerManage;
class AppUserInterfaceManage;
class AppDataManage;

class AppInstance : public QObject, public IAppCore, public IAppResourceCore {
	Q_OBJECT;

private:
	static AppInstance *instance;

protected:
	class AppParam {
		friend class AppInstance;
		friend class ApplicationManage;
		int argc;
		char **argv;
		int app_flag_s;

	public:
		virtual ~AppParam( );

		AppParam( int argc, char **argv, int app_flag_s );

		virtual int getArgc( ) const;

		virtual char ** getArgv( ) const;

		virtual int getAppFlagS( ) const;
	};

	/// @brief app 运行参数
	AppParam appParam;
	/// @brief 应用循环
	ApplicationManage *applicationManage = nullptr;
	/// @brief 数据管理
	AppDataManage *appDataManage = nullptr;
	/// @brief 用户界面
	AppUserInterfaceManage *appUserInterfaceManage = nullptr;
	/// @brief 时间管理
	AppDateTimerManage *appDateTimerManage = nullptr;

public:
	static AppInstance * getAppInstance( );

	AppInstance( int &argc, char **argv, int app_flag_s = QCoreApplication::ApplicationFlags );

	~AppInstance( ) override;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;
	virtual int exec( );
	virtual int quit();
protected:
	bool deleteResource( ) override;

public:
	virtual AppDataManage * getAppDataManage( ) const;

	virtual AppUserInterfaceManage * getAppUserInterfaceManage( ) const;

	virtual AppDateTimerManage * getAppDateTimerManage( ) const;

	virtual ApplicationManage * getApplicationManage( ) const;
};
#endif // APPINSTANCE_H_H_HEAD__FILE__
