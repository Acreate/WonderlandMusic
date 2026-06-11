#ifndef APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
#define APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__

#include <base/baseObject/baseObject.h>
#include <macro/eventMacroDefine.h>
#include <functional>

Event_Declare_Event_Info_Type_Name( ApplicationInstance );
Event_Declare_Event_Info_Type_Name( MainWindow );
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
Event_Declare_Event_Info_Type_Name( MusicCollectionWidget );
Event_Declare_Event_Info_Type_Name( MusicCollectionTopMenu );
Event_Declare_Event_Info_Type_Name( MusicCollectionSubMenu );
Event_Declare_Event_Info_Type_Name( MusicListTopMenu );
Event_Declare_Event_Info_Type_Name( MusicListSubMenu );

class ApplicationEvenTrigger : public BaseObject {
	/// @brief 事件友元，用于初始化
	friend class InitApplicationInstance;
private:
	Event_Define_Event_Friend_Type_Name( ApplicationInstance );
	Event_Define_Event_Friend_Type_Name( MainWindow );
	Event_Define_Event_Friend_Type_Name( OptionNavigationWidget );
	Event_Define_Event_Friend_Type_Name( OptionNavigationDockWidget );
	Event_Define_Event_Friend_Type_Name( SettingWindow );
	Event_Define_Event_Friend_Type_Name( CoreStackedWidget );
	Event_Define_Event_Friend_Type_Name( FindDockWidget );
	Event_Define_Event_Friend_Type_Name( PlayerDockWidget );
	Event_Define_Event_Friend_Type_Name( CoreWindow );
	Event_Define_Event_Friend_Type_Name( FunctionWidget );
	Event_Define_Event_Friend_Type_Name( TopToolWidget );
	Event_Define_Event_Friend_Type_Name( FunctionDockWidget );
	Event_Define_Event_Friend_Type_Name( TopToolDockWidget );
	Event_Define_Event_Friend_Type_Name( ContentWindow );
	Event_Define_Event_Friend_Type_Name( PlayerWidget );
	Event_Define_Event_Friend_Type_Name( PathSettingWidget );
	Event_Define_Event_Friend_Type_Name( MusicListMainWidget );
	Event_Define_Event_Friend_Type_Name( MusicCollectionWidget );
	Event_Define_Event_Friend_Type_Name( MusicCollectionTopMenu );
	Event_Define_Event_Friend_Type_Name( MusicCollectionSubMenu );
	Event_Define_Event_Friend_Type_Name( MusicListTopMenu );
	Event_Define_Event_Friend_Type_Name( MusicListSubMenu );
private:
	Q_OBJECT;
protected:
	ApplicationInstance *application;
	static ApplicationInstance * getApplication( );
	static ApplicationEvenTrigger * getApplicationEvenTrigger( ApplicationInstance *application );
public:
	ApplicationEvenTrigger( ApplicationInstance *application );
public:
	Event_Define_Quick_Connect_Signed( ApplicationInstance );
	Event_Define_Quick_Connect_Signed( MainWindow );
	Event_Define_Quick_Connect_Signed( OptionNavigationWidget );
	Event_Define_Quick_Connect_Signed( OptionNavigationDockWidget );
	Event_Define_Quick_Connect_Signed( SettingWindow );
	Event_Define_Quick_Connect_Signed( CoreStackedWidget );
	Event_Define_Quick_Connect_Signed( FindDockWidget );
	Event_Define_Quick_Connect_Signed( PlayerDockWidget );
	Event_Define_Quick_Connect_Signed( CoreWindow );
	Event_Define_Quick_Connect_Signed( FunctionWidget );
	Event_Define_Quick_Connect_Signed( TopToolWidget );
	Event_Define_Quick_Connect_Signed( FunctionDockWidget );
	Event_Define_Quick_Connect_Signed( TopToolDockWidget );
	Event_Define_Quick_Connect_Signed( ContentWindow );
	Event_Define_Quick_Connect_Signed( PlayerWidget );
	Event_Define_Quick_Connect_Signed( PathSettingWidget );
	Event_Define_Quick_Connect_Signed( MusicListMainWidget );
	Event_Define_Quick_Connect_Signed( MusicCollectionWidget );
	Event_Define_Quick_Connect_Signed( MusicCollectionTopMenu );
	Event_Define_Quick_Connect_Signed( MusicCollectionSubMenu );
	Event_Define_Quick_Connect_Signed( MusicListTopMenu );
	Event_Define_Quick_Connect_Signed( MusicListSubMenu );

Q_SIGNALS:
	Event_Define_Receive_Call_Function( ApplicationInstance );
	Event_Define_Receive_Call_Function( MainWindow );
	Event_Define_Receive_Call_Function( OptionNavigationWidget );
	Event_Define_Receive_Call_Function( OptionNavigationDockWidget );
	Event_Define_Receive_Call_Function( SettingWindow );
	Event_Define_Receive_Call_Function( CoreStackedWidget );
	Event_Define_Receive_Call_Function( FindDockWidget );
	Event_Define_Receive_Call_Function( PlayerDockWidget );
	Event_Define_Receive_Call_Function( CoreWindow );
	Event_Define_Receive_Call_Function( FunctionWidget );
	Event_Define_Receive_Call_Function( TopToolWidget );
	Event_Define_Receive_Call_Function( FunctionDockWidget );
	Event_Define_Receive_Call_Function( TopToolDockWidget );
	Event_Define_Receive_Call_Function( ContentWindow );
	Event_Define_Receive_Call_Function( PlayerWidget );
	Event_Define_Receive_Call_Function( PathSettingWidget );
	Event_Define_Receive_Call_Function( MusicListMainWidget );
	Event_Define_Receive_Call_Function( MusicCollectionWidget );
	Event_Define_Receive_Call_Function( MusicCollectionTopMenu );
	Event_Define_Receive_Call_Function( MusicCollectionSubMenu );
	Event_Define_Receive_Call_Function( MusicListTopMenu );
	Event_Define_Receive_Call_Function( MusicListSubMenu );
};

Event_Define_Event_Class_type( ApplicationInstance, ApplicationEvenTrigger );
Event_Define_Event_Class_type( MainWindow, ApplicationEvenTrigger );
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
Event_Define_Event_Class_type( MusicCollectionWidget, ApplicationEvenTrigger );
Event_Define_Event_Class_type( MusicCollectionTopMenu, ApplicationEvenTrigger );
Event_Define_Event_Class_type( MusicCollectionSubMenu, ApplicationEvenTrigger );
Event_Define_Event_Class_type( MusicListTopMenu, ApplicationEvenTrigger );
Event_Define_Event_Class_type( MusicListSubMenu, ApplicationEvenTrigger );

#endif // APPLICATIONEVENTRIGGER_H_H_HEAD__FILE__
