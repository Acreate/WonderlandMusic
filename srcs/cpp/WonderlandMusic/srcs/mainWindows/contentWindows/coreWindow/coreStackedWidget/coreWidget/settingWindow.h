#ifndef SETTINGWINDOW_H_H_HEAD__FILE__
#define SETTINGWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
#include <macro/eventMacroDefine.h>

#define OptionNavigationWidgetEventClassName Event_Default_Event_Class_Type_Name( OptionNavigationDockWidget )
#define OptionNavigationWidgetDefaultEventCallFunction Event_Default_Receive_Call_Function( OptionNavigationDockWidget )
#define OptionNavigationWidgetEventDefineClass Event_Define_Event_Class_type( OptionNavigationDockWidget, SettingWindow )
class OptionNavigationDockWidget;
class Event_Default_Event_Info_Type_Name( OptionNavigationDockWidget );

class CoreStackedWidget;
class OptionStackWidget;
class OptionNavigationWidget;
class SettingWindow : public QMainWindow {
	friend class OptionNavigationWidgetEventClassName;
	Q_OBJECT;
protected:
	CoreStackedWidget *coreStackedWidget;
	OptionNavigationDockWidget* optionNavigationDockWidget;
	OptionStackWidget* optionStackWidget;
public:
	SettingWindow( CoreStackedWidget *parent );
private:
	virtual OptionNavigationWidgetDefaultEventCallFunction;
};

#define SettingWindowEventTypeName Event_Default_Event_Info_Type_Name( SettingWindow )
class SettingWindowEventTypeName {

};

OptionNavigationWidgetEventDefineClass;
#endif // SETTINGWINDOW_H_H_HEAD__FILE__
