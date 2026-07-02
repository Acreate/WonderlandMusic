#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../application/appCore.h"
#include "../application/appDiskJsonData.h"
class MainStackedWidget;
class OptionDockWidget;
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

class MainWindow : public QMainWindow, public AppCore, public AppDiskJsonData {
	Q_OBJECT;

protected:
	/// @brief 获取 app 实例
	AppInstance *appInstance;
	/// @brief 获取软件翻译
	const AppTranslate *appTranslate;
	/// @brief 获取 Json 关键字信息
	const JsonFileKey *jsonFileKey;
	/// @brief 配置主显示组件-层叠
	MainStackedWidget *mainStackedWidget = nullptr;
	/// @brief 在主窗口配置左侧容器窗口
	OptionDockWidget *leftOptionDockWidget = nullptr;
	/// @brief 是否初始化
	bool isLoadJsonFile;

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

	bool event( QEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
