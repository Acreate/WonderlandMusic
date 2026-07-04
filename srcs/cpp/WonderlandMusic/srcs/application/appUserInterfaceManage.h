#ifndef APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"

class AppDrawManage;
class PlayerListTopWidget;
class MainWindow;
class SystemTrayIcon;

class AppUserInterfaceManage : public QObject, public IAppCore {
	Q_OBJECT;

protected:
	/// @brief 主要执行窗口
	MainWindow *mainWindow = nullptr;
	/// @brief 系统托盘
	SystemTrayIcon *systemTrayIcon = nullptr;

	/// @brief 绘制管理
	AppDrawManage *appDrawManage = nullptr;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	~AppUserInterfaceManage( ) override;

	virtual bool showMainWindow( ) const;

	virtual bool hideMainWindow( ) const;

	virtual MainWindow * getMainWindow( ) const;

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const;

	virtual AppDrawManage * getAppDrawManage( ) const;
};

#endif // APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
