#ifndef APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#include <interface/iAppCore.h>
#include <interface/iAppJsonData.h>

class AppMenuManage;
class AppDrawManage;
class SystemTrayIcon;
class MainWindow;

class AppUserInterfaceManage : public QObject, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	/// @brief 主要执行窗口
	MainWindow *mainWindow = nullptr;
	/// @brief 系统托盘
	SystemTrayIcon *systemTrayIcon = nullptr;
	/// @brief 绘制管理
	AppDrawManage *appDrawManage = nullptr;
	/// @brief 菜单管理
	AppMenuManage *appMenuManage = nullptr;

protected:
	bool deleteResource( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
	~AppUserInterfaceManage( ) override;
	virtual AppMenuManage * getAppMenuManage( ) const;
	virtual bool showMainWindow( ) const;
	virtual bool hideMainWindow( ) const;
	virtual MainWindow * getMainWindow( ) const;
	virtual SystemTrayIcon * getSystemTrayIcon( ) const;
	virtual AppDrawManage * getAppDrawManage( ) const;
};
#endif // APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
