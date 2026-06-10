#ifndef SETTINGWINDOW_H_H_HEAD__FILE__
#define SETTINGWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
#include <macro/eventMacroDefine.h>

#include <base/baseWindow/baseMainWindow.h>

class OptionNavigationDockWidget;
class CoreStackedWidget;
class OptionStackWidget;
class OptionNavigationWidget;
class SettingWindow : public BaseMainWindow {
	Q_OBJECT;
protected:
	CoreStackedWidget *coreStackedWidget;
	OptionNavigationDockWidget *optionNavigationDockWidget;
	OptionStackWidget *optionStackWidget;
public:
	SettingWindow( CoreStackedWidget *parent );
private:
};

#define SettingWindowEventTypeName Event_Define_Event_Info_Type_Name( SettingWindow )
class SettingWindowEventTypeName {

};

#endif // SETTINGWINDOW_H_H_HEAD__FILE__
