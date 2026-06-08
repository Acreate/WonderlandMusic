#ifndef APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
#define APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__

#include <base/baseObject/baseObject.h>
#include <macro/eventMacroDefine.h>

Event_Declare_Event_Info_Type_Name( ApplicationInstance );
Event_Declare_Event_Info_Type_Name( MainWindow );
Event_Declare_Event_Info_Type_Name( ControlCollectionMenu );
Event_Declare_Event_Info_Type_Name( ControlMusicListMenu );
Event_Declare_Event_Info_Type_Name( OptionNavigationWidget );
Event_Declare_Event_Info_Type_Name( OptionNavigationDockWidget );
Event_Declare_Event_Info_Type_Name( SettingWindow );
Event_Declare_Event_Info_Type_Name( CoreStackedWidget );
Event_Declare_Event_Info_Type_Name( FindDockWidget );
Event_Declare_Event_Info_Type_Name( PlayerDockWidget );
Event_Declare_Event_Info_Type_Name( CoreWindow );
Event_Declare_Event_Info_Type_Name( FunctionWidget );
Event_Declare_Event_Info_Type_Name( TopToolWidget );
Event_Declare_Event_Info_Type_Name( FunctionDockWidget );
Event_Declare_Event_Info_Type_Name( TopToolDockWidget );
Event_Declare_Event_Info_Type_Name( ContentWindow );
Event_Declare_Event_Info_Type_Name( PlayerWidget );
Event_Declare_Event_Info_Type_Name( PathSettingWidget );
Event_Declare_Event_Info_Type_Name( MusicListMainWidget );
Event_Declare_Event_Info_Type_Name( CollectionTopToolWidget );
Event_Declare_Event_Info_Type_Name( CollectionItemWidget );

class ApplicationEvenTrigger : public BaseObject {
	/// @brief 事件友元，用于初始化
	friend class InitApplicationInstance;
private:
	friend class Event_Default_Event_Info_Type_Name( ApplicationInstance );
	friend class Event_Default_Event_Info_Type_Name( MainWindow );
	friend class Event_Default_Event_Info_Type_Name( ControlCollectionMenu );
	friend class Event_Default_Event_Info_Type_Name( ControlMusicListMenu );
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
	friend class Event_Default_Event_Info_Type_Name( MusicListMainWidget );
	friend class Event_Default_Event_Info_Type_Name( CollectionTopToolWidget );
	friend class Event_Default_Event_Info_Type_Name( CollectionItemWidget );
private:
	Q_OBJECT;
protected:
	ApplicationInstance *application;
public:
	ApplicationEvenTrigger( ApplicationInstance *application );
Q_SIGNALS:
	Event_Default_Receive_Call_Function( ApplicationInstance );
	Event_Default_Receive_Call_Function( MainWindow );
	Event_Default_Receive_Call_Function( ControlCollectionMenu );
	Event_Default_Receive_Call_Function( ControlMusicListMenu );
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
	Event_Default_Receive_Call_Function( MusicListMainWidget );
	Event_Default_Receive_Call_Function( CollectionTopToolWidget );
	Event_Default_Receive_Call_Function( CollectionItemWidget );
};

Event_Define_Event_Class_type( ApplicationInstance, ApplicationEvenTrigger );
Event_Define_Event_Class_type( MainWindow, ApplicationEvenTrigger );
Event_Define_Event_Class_type( ControlCollectionMenu, ApplicationEvenTrigger );
Event_Define_Event_Class_type( ControlMusicListMenu, ApplicationEvenTrigger );
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
Event_Define_Event_Class_type( MusicListMainWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( CollectionTopToolWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( CollectionItemWidget, ApplicationEvenTrigger );

#endif // APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
