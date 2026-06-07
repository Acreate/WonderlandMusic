#ifndef APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
#define APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
#include <QObject>

#include "../macro/eventMacroDefine.h"

class ApplicationInstance;
class OptionNavigationWidget;
class Event_Default_Event_Info_Type_Name( OptionNavigationWidget );

class OptionNavigationDockWidget;
class Event_Default_Event_Info_Type_Name( OptionNavigationDockWidget );

class SettingWindow;
class Event_Default_Event_Info_Type_Name( SettingWindow );

class CoreStackedWidget;
class Event_Default_Event_Info_Type_Name( CoreStackedWidget );

class FindDockWidget;
class Event_Default_Event_Info_Type_Name( FindDockWidget );

class PlayerDockWidget;
class Event_Default_Event_Info_Type_Name( PlayerDockWidget );

class CoreWindow;
class Event_Default_Event_Info_Type_Name( CoreWindow );

class FunctionWidget;
class Event_Default_Event_Info_Type_Name( FunctionWidget );

class TopToolWidget;
class Event_Default_Event_Info_Type_Name( TopToolWidget );

class FunctionDockWidget;
class Event_Default_Event_Info_Type_Name( FunctionDockWidget );

class TopToolDockWidget;
class Event_Default_Event_Info_Type_Name( TopToolDockWidget );

class ContentWindow;
class Event_Default_Event_Info_Type_Name( ContentWindow );

class PlayerWidget;
class Event_Default_Event_Info_Type_Name( PlayerWidget );

class PathSettingWidget;
class Event_Default_Event_Info_Type_Name( PathSettingWidget );

class ApplicationEvenTrigger : public QObject {
	/// @brief 事件友元
private:
	friend class Event_Default_Event_Info_Type_Name( OptionNavigationWidget );
	friend class Event_Default_Event_Info_Type_Name( OptionNavigationDockWidget );
	friend class Event_Default_Event_Info_Type_Name( SettingWindow );
	friend class Event_Default_Event_Info_Type_Name( CoreStackedWidget );
	friend class Event_Default_Event_Info_Type_Name( FindDockWidget );
	friend class Event_Default_Event_Info_Type_Name( PlayerDockWidget );
	friend class Event_Default_Event_Info_Type_Name( CoreWindow );
	friend class Event_Default_Event_Info_Type_Name( FunctionWidget );
	friend class Event_Default_Event_Info_Type_Name( TopToolWidget );
	friend class Event_Default_Event_Info_Type_Name( FunctionDockWidget );
	friend class Event_Default_Event_Info_Type_Name( TopToolDockWidget );
	friend class Event_Default_Event_Info_Type_Name( ContentWindow );
	friend class Event_Default_Event_Info_Type_Name( PlayerWidget );
	friend class Event_Default_Event_Info_Type_Name( PathSettingWidget );
private:
	Q_OBJECT;
protected:
	ApplicationInstance *application;
public:
	ApplicationEvenTrigger( ApplicationInstance *application );
Q_SIGNALS:
	Event_Default_Receive_Call_Function( OptionNavigationWidget );
	Event_Default_Receive_Call_Function( OptionNavigationDockWidget );
	Event_Default_Receive_Call_Function( SettingWindow );
	Event_Default_Receive_Call_Function( CoreStackedWidget );
	Event_Default_Receive_Call_Function( FindDockWidget );
	Event_Default_Receive_Call_Function( PlayerDockWidget );
	Event_Default_Receive_Call_Function( CoreWindow );
	Event_Default_Receive_Call_Function( FunctionWidget );
	Event_Default_Receive_Call_Function( TopToolWidget );
	Event_Default_Receive_Call_Function( FunctionDockWidget );
	Event_Default_Receive_Call_Function( TopToolDockWidget );
	Event_Default_Receive_Call_Function( ContentWindow );
	Event_Default_Receive_Call_Function( PlayerWidget );
	Event_Default_Receive_Call_Function( PathSettingWidget );
};

Event_Define_Event_Class_type( OptionNavigationWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( OptionNavigationDockWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( SettingWindow, ApplicationEvenTrigger );
Event_Define_Event_Class_type( CoreStackedWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( FindDockWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( PlayerDockWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( CoreWindow, ApplicationEvenTrigger );
Event_Define_Event_Class_type( FunctionWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( TopToolWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( FunctionDockWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( TopToolDockWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( ContentWindow, ApplicationEvenTrigger );
Event_Define_Event_Class_type( PlayerWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( PathSettingWidget, ApplicationEvenTrigger );

#endif // APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
