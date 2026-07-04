#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class PlayerListTopWidget;
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

class MainWindow : public QMainWindow, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	/// @brief 配置主显示组件-层叠
	MainStackedWidget *mainStackedWidget = nullptr;
	/// @brief 在主窗口配置左侧容器窗口
	OptionDockWidget *leftOptionDockWidget = nullptr;

public:
	~MainWindow( ) override;

	MainWindow( QWidget *parent, Qt::WindowFlags flags );

	MainWindow( QWidget *parent );

	MainWindow( Qt::WindowFlags flags );

	MainWindow( );

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	bool init( ) override;

protected:
	bool deleteResource( ) override;

	bool event( QEvent *event ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
