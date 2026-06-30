#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../application/appCore.h"
#include "../application/appJsonData.h"
class PlayerWindow;
class QScrollArea;
class QPushButton;
class JsonFileKey;
class QStackedWidget;
class PlayerListWidget;
class SettingWidget;
class AboutWidget;
class AppTranslate;
class AppInstance;

class MainWindow : public QMainWindow, public AppCore , public AppJsonData{
	Q_OBJECT;

protected:
	/// @brief 获取 app 实例
	AppInstance *appInstance;
	/// @brief 获取软件翻译
	const AppTranslate *appTranslate;
	/// @brief 获取 Json 关键字信息
	const JsonFileKey *jsonFileKey;
	/// @brief 配置主显示组件-层叠
	QStackedWidget *mainStackedWidget = nullptr;
	/// @brief 播放窗口
	PlayerWindow *playerWindow = nullptr;
	/// @brief 在层叠组件配置设置组件
	SettingWidget *settingWidget = nullptr;
	/// @brief 在层叠组件配置关于组件
	AboutWidget *aboutWidget = nullptr;
	/// @brief 在主窗口配置左侧容器窗口
	QDockWidget *leftOptionDockWidget = nullptr;
	// 在左容器窗口配置按钮组件
	QWidget *leftOptionWidget = nullptr;
	/// @brief 显示播放列表按钮
	QPushButton *showPlayListWidgetBtn = nullptr;
	/// @brief 显示软件设置按钮
	QPushButton *showSettingWidgetBtn = nullptr;
	/// @brief 显示关于面板按钮
	QPushButton *showAboutWidgetBtn = nullptr;
	/// @brief 是否初始化
	bool isLoadJsonFile;

protected:
	/// @brief 初始化 AppInstance 实例相关对象
	/// @return 失败返回 false
	virtual bool initApp( );

	/// @brief 初始化层叠组件
	/// @return 失败返回 false
	virtual bool initStackedWidget( );

	/// @brief 初始化停靠容器组件
	/// @return 失败返回 false
	virtual bool initDockWidget( );

	/// @brief 初始化主窗口配置
	/// @return 失败返回 false
	virtual bool initMainWindowSetting( );

	/// @brief 初始化信息
	/// @return 失败返回 false
	virtual bool initConnect( );

	/// @brief 保存主窗口配置
	/// @return 失败返回 false
	virtual bool saveMainWindowSetting( );

	/// @brief 初始化子控件
	/// @return 失败返回 false
	virtual bool subCompomentInit( );

public:
	~MainWindow( ) override;

	MainWindow( QWidget *parent, Qt::WindowFlags flags );

	MainWindow( QWidget *parent );

	MainWindow( Qt::WindowFlags flags );

	MainWindow( );

protected:
	bool readJsonData( ) override;

	bool writeJsonData( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;


	bool init( ) override;

protected:
	bool deleteResource( ) override;

	//void closeEvent( QCloseEvent *event ) override;
	bool event( QEvent *event ) override;

	void showEvent( QShowEvent *event ) override;

	void closeEvent( QCloseEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
