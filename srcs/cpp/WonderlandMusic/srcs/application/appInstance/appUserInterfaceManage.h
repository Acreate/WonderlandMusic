#ifndef APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#define APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
#include <interface/iAppJsonData.h>

#include <interface/iAppResourceCore.h>

#include "../../classTypeInfo/classTypeInfoVar.h"

#include "../../component/playWindow/interface/widget/iPlayerWindowCentreWidget.h"

class PlayerControlWidget;
class PlayerWindowCentreWidget;
class PlayerInfoListWidget;
class PlayWindow;
class IMusicTitleWidget;
class IMusicListWidget;
class IMusicFavoriteWidget;
class IMusicCentreWidget;
class MusicCentreWidget;
class OptionWindow;
class MusicWindow;
class SettingWidget;
class AboutWidget;
class MusicFavoriteWidget;
class MusicListWidget;
class MusicTitleWidget;
class AppMenuManage;
class AppDrawManage;
class SystemTrayIcon;
class MainWindow;

class AppUserInterfaceManage : public QObject, public IAppJsonData, public IAppResourceCore, public ClassTypeInfoVar {
	Q_OBJECT;

protected:
	UserMutex* userMutex = nullptr;
	/// @brief 主要执行窗口
	MainWindow *mainWindow = nullptr;
	/// @brief 播放窗口
	PlayWindow *playWindow = nullptr;
	/// @brief 播放窗口内容组件
	PlayerWindowCentreWidget *playerWindowCentreWidget = nullptr;
	/// @brief 播放窗口控制组件
	PlayerControlWidget *playerControlWidget = nullptr;
	/// @brief 播放窗口列表组件
	PlayerInfoListWidget *playerInfoListWidget = nullptr;
	/// @brief 音频窗口
	MusicWindow *musicWindow = nullptr;
	/// @brief 配置窗口组件
	SettingWidget *settingWidget = nullptr;
	/// @brief 关于窗口组件
	AboutWidget *aboutWidget = nullptr;
	/// @brief 音频主要组件
	MusicCentreWidget *musicCentreWidget = nullptr;
	/// @brief 音频收藏列表窗口组件
	MusicFavoriteWidget *musicFavoriteWidget = nullptr;
	/// @brief 音频信息列表窗口组件
	MusicListWidget *musicListWidget = nullptr;
	/// @brief 音频列表标题窗口组件
	MusicTitleWidget *musicTitleWidget = nullptr;
	/// @brief 系统托盘
	SystemTrayIcon *systemTrayIcon = nullptr;
	/// @brief 绘制管理
	AppDrawManage *appDrawManage = nullptr;
	/// @brief 菜单管理
	AppMenuManage *appMenuManage = nullptr;

protected:
	bool deleteResource( );

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
	AppUserInterfaceManage( );
	~AppUserInterfaceManage( ) override;
	virtual AppMenuManage * getAppMenuManage( ) const;
	virtual bool showMainWindow( ) const;
	virtual bool hideMainWindow( ) const;
	virtual MainWindow * getMainWindow( ) const;
	virtual SystemTrayIcon * getSystemTrayIcon( ) const;
	virtual AppDrawManage * getAppDrawManage( ) const;
	virtual PlayerInfoListWidget * getPlayerInfoListWidget( ) const;
	virtual MusicWindow * getMusicWindow( ) const;
	virtual SettingWidget * getSettingWidget( ) const;
	virtual AboutWidget * getAboutWidget( ) const;
	virtual IMusicCentreWidget * getMusicCentreWidget( ) const;
	virtual IMusicFavoriteWidget * getMusicFavoriteWidget( ) const;
	virtual IMusicListWidget * getMusicListWidget( ) const;
	virtual IMusicTitleWidget * getMusicTitleWidget( ) const;
	virtual PlayWindow * getPlayWindow( ) const;
	virtual IPlayerWindowCentreWidget * getPlayerWindowCentreWidget( ) const;
	virtual IPlayerControlWidget * getPlayerControlWidget( ) const;
};
#endif // APPUSERINTERFACEMANAGE_H_H_HEAD__FILE__
