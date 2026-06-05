#ifndef SETTINGWINDOW_H_H_HEAD__FILE__
#define SETTINGWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
class CoreStackedWidget;
class SettingWindow : public QMainWindow {
	Q_OBJECT;
protected:
	CoreStackedWidget *coreStackedWidget;
public:
	SettingWindow( CoreStackedWidget *parent );
};

#endif // SETTINGWINDOW_H_H_HEAD__FILE__
