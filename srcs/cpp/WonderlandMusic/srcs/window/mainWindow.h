#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
class PlayerWindow;
class QScrollArea;
class QPushButton;
class JsonFileKey;
class QStackedWidget;
class PlayListWidget;
class SettingWidget;
class AboutWidget;
class AppTranslate;
class AppInstance;

class MainWindow : public QMainWindow {
	Q_OBJECT;

protected:
	/// @brief 获取 app 实例
	AppInstance *appInstance;
	/// @brief 获取软件翻译
	const AppTranslate *appTranslate;
	/// @brief 获取 Json 关键字信息
	const JsonFileKey *jsonFileKey;
	/// @brief 配置主显示组件-层叠
	QStackedWidget *mainStackedWidget;
	/// @brief 播放窗口
	PlayerWindow *playerWindow;
	/// @brief 在层叠组件配置设置组件
	SettingWidget *settingWidget;
	/// @brief 在层叠组件配置关于组件
	AboutWidget *aboutWidget;
	/// @brief 在主窗口配置左侧容器窗口
	QDockWidget *leftOptionDockWidget;
	// 在左容器窗口配置按钮组件
	QWidget *leftOptionWidget;
	/// @brief 显示播放列表按钮
	QPushButton *showPlayListWidgetBtn;
	/// @brief 显示软件设置按钮
	QPushButton *showSettingWidgetBtn;
	/// @brief 显示关于面板按钮
	QPushButton *showAboutWidgetBtn;
	/// @brief 是否初始化
	bool isLoadJsonFile;

protected:
	/// @brief 初始化 AppInstance 实例相关对象
	/// @return 失败返回 false
	bool initApp( );

	/// @brief 初始化层叠组件
	/// @return 失败返回 false
	bool initStackedWidget( );

	/// @brief 初始化停靠容器组件
	/// @return 失败返回 false
	bool initDockWidget( );

	/// @brief 初始化主窗口配置
	/// @return 失败返回 false
	bool initMainWindowSetting( );

	/// @brief 初始化信息
	/// @return 失败返回 false
	bool initConnect( );

	/// @brief 保存主窗口配置
	/// @return 失败返回 false
	bool saveMainWindowSetting( );

	void hideEvent( QHideEvent *event ) override;

public:
	~MainWindow( ) override;

	MainWindow( QWidget *parent, Qt::WindowFlags flags );

	bool loadSettingWidgetInfoAtFile( );

	MainWindow( QWidget *parent );

	MainWindow( Qt::WindowFlags flags );

	MainWindow( );

	void writeWidgetSettingToFile( );

	virtual bool init( );

protected:
	void showEvent( QShowEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
