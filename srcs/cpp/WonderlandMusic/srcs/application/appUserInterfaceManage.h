#ifndef APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#include "appCore.h"

class MainWindow;
class SystemTrayIcon;

class AppUserInterfaceManage : public AppCore {
protected:
	/// @brief 主要执行窗口
	MainWindow *mainWindow = nullptr;
	/// @brief 系统托盘
	SystemTrayIcon *systemTrayIcon = nullptr;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	~AppUserInterfaceManage( ) override;

	virtual bool showMainWindow( ) const;

	virtual bool hideMainWindow( ) const;

	virtual MainWindow * getMainWindow( ) const;
};

#endif // APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
