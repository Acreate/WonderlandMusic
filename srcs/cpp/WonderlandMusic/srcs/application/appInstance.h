#ifndef APPINSTANCE_H_H_HEAD__FILE__
#define APPINSTANCE_H_H_HEAD__FILE__

#include <QApplication>

#include "appCore.h"

class MusicManage;
class AppDateTimerManage;
class AppUserInterfaceManage;
class AppDrawManage;
class AppDataManage;
class SystemTrayIcon;
class RenderImage;
class MainWindow;
class JsonFileKey;
class MusicDecoder;
class AppTranslate;
class MessageErrorOut;

class AppInstance : public QApplication, public AppCore {
	Q_OBJECT;

private:
	static AppInstance *instance;

protected:
	/// @brief 数据管理
	AppDataManage *appDataManage = nullptr;
	/// @brief 绘制管理
	AppDrawManage *appDrawManage = nullptr;
	/// @brief 用户界面
	AppUserInterfaceManage *appUserInterfaceManage = nullptr;
	/// @brief 时间管理
	AppDateTimerManage *appDateTimerManage = nullptr;
	/// @brief 音频管理
	MusicManage *musicManage = nullptr;

public:
	static AppInstance * getAppInstance( );

	AppInstance( int &argc, char **argv, int app_flag_s = ApplicationFlags );

	~AppInstance( ) override;

	bool notify( QObject *, QEvent * ) override;

	bool init( ) override;

protected:
	bool deleteResource( ) override;

public:
	virtual AppDataManage * getAppDataManage( ) const;

	virtual AppDrawManage * getAppDrawManage( ) const;

	virtual AppUserInterfaceManage * getAppUserInterfaceManage( ) const;

	virtual AppDateTimerManage * getAppDateTimerManage( ) const;

	virtual MusicManage * getMusicManage( ) const;
};
#endif // APPINSTANCE_H_H_HEAD__FILE__
