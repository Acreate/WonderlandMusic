#ifndef APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"
#include "../interface/iAppDiskJsonData.h"

class AppMenuManage;
class LabelWidget;
class AppDrawManage;
class PlayerListTopWidget;
class MainWindow;
class SystemTrayIcon;

class AppUserInterfaceManage : public QObject, public IAppCore, public IAppDiskJsonData {
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
	virtual AppMenuManage * getAppMenuManage( ) const;

	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	bool readJsonData( ) override;

	bool writeJsonData( ) override;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	~AppUserInterfaceManage( ) override;

	virtual bool showMainWindow( ) const;

	virtual bool hideMainWindow( ) const;

	virtual MainWindow * getMainWindow( ) const;

	virtual AppDrawManage * getAppDrawManage( ) const;

	virtual bool appendFavoriteItem( const QString &create_favorite_name );

	virtual bool removeFavoriteItem( const QString &remove_favorite_name );

	virtual bool resetFavoriteItem( const std::vector< QString > &create_favorite_vector );

Q_SIGNALS:


};

#endif // APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
