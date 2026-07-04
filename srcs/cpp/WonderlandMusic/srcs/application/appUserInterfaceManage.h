#ifndef APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"
#include "../interface/iAppDiskJsonData.h"

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

protected:
	bool deleteResource( ) override;

public:
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

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const;

	virtual AppDrawManage * getAppDrawManage( ) const;

Q_SIGNALS:
	void signal_change_setting_path( const QString &new_setting_home_path );

	void signal_changed_width( int split_width, int widget_before_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width );

	void signal_horizontal_scroll_set_value( int value );
};

#endif // APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
