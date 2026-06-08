#ifndef OPTIONNAVIGATIONDOCKWIDGET_H_H_HEAD__FILE__
#define OPTIONNAVIGATIONDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
#include <macro/eventMacroDefine.h>

#include "../../../../../../baseWidget/baseDockWidget.h"

class OptionNavigationWidget;
class QPushButton;
class SettingWindow;
/// @brief 导航选项窗口
class OptionNavigationDockWidget : public BaseDockWidget {
	Q_OBJECT;
protected:
	SettingWindow *settingWindow;
	OptionNavigationWidget *optionNavigationWidget;
public:
	OptionNavigationDockWidget( SettingWindow *parent );
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

#endif // OPTIONNAVIGATIONDOCKWIDGET_H_H_HEAD__FILE__
