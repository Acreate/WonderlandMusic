#ifndef OPTIONDOCKWIDGET_H_H_HEAD__FILE__
#define OPTIONDOCKWIDGET_H_H_HEAD__FILE__
#include <QDockWidget>

#include "../interface/iAppCore.h"

class QPushButton;
class MainWindow;

class OptionDockWidget : public QDockWidget, public IAppCore {
	Q_OBJECT;

protected:
	MainWindow *mainWindow;
	/// @brief 标题组件
	QWidget *titleBarWidget = nullptr;
	/// @brief 选项列表组件
	QWidget *leftOptionWidget = nullptr;
	/// @brief 显示播放列表按钮
	QPushButton *showPlayListWidgetBtn = nullptr;
	/// @brief 显示软件设置按钮
	QPushButton *showSettingWidgetBtn = nullptr;
	/// @brief 显示关于面板按钮
	QPushButton *showAboutWidgetBtn = nullptr;

public:
	OptionDockWidget( MainWindow *parent );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

Q_SIGNALS:
	void signal_click_player_button( );

	void signal_click_setting_button( );

	void signal_click_about_button( );
};

#endif // OPTIONDOCKWIDGET_H_H_HEAD__FILE__
