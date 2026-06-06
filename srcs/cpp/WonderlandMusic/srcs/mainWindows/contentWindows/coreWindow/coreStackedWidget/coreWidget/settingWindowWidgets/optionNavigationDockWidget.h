#ifndef OPTIONNAVIGATIONDOCKWIDGET_H_H_HEAD__FILE__
#define OPTIONNAVIGATIONDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
#include <macro/eventMacroDefine.h>

class OptionNavigationWidget;
class QPushButton;
class SettingWindow;
/// @brief 导航选项窗口
class OptionNavigationDockWidget : public QDockWidget {
	friend class Event_Default_Event_Info_Type_Name( OptionNavigationWidget );
	Q_OBJECT;
protected:
	SettingWindow *settingWindow;
	OptionNavigationWidget *optionNavigationWidget;
public:
	OptionNavigationDockWidget( SettingWindow *parent );
	virtual Event_Default_Receive_Call_Function( OptionNavigationWidget );
};

class Event_Default_Event_Info_Type_Name( OptionNavigationDockWidget ) {
public:
	enum class EventType {
		None,
		Show_Path_Widget,
		Show_About_Widget,
	};
protected:
	EventType eventType;
public:
	virtual ~Event_Default_Event_Info_Type_Name( OptionNavigationDockWidget )( ) = default;
	Event_Default_Event_Info_Type_Name( OptionNavigationDockWidget )( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};

Event_Define_Event_Class_type( OptionNavigationWidget, OptionNavigationDockWidget );
#endif // OPTIONNAVIGATIONDOCKWIDGET_H_H_HEAD__FILE__
