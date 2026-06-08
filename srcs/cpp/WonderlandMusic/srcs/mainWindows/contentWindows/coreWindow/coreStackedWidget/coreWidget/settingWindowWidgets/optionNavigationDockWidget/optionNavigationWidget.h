#ifndef OPTIONNAVIGATIONWIDGET_H_H_HEAD__FILE__
#define OPTIONNAVIGATIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>
#include <macro/eventMacroDefine.h>

#include "../../../../../../../baseWidget/baseWidget.h"

class QPushButton;
class OptionNavigationDockWidget;
class OptionNavigationWidget : public BaseWidget {
	Q_OBJECT;
protected:
	OptionNavigationDockWidget *optionNavigationDockWidget;
	QPushButton *pathBtn;
	QPushButton *aboutBtn;
public:
	OptionNavigationWidget( OptionNavigationDockWidget *parent );
};

class Event_Default_Event_Info_Type_Name( OptionNavigationWidget ) {
public:
	enum class EventType {
		None,
		Show_Path_Widget,
		Show_About_Widget,
	};
protected:
	EventType eventType;
public:
	virtual ~OptionNavigationWidgetEventInfo( ) = default;
	OptionNavigationWidgetEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // OPTIONNAVIGATIONWIDGET_H_H_HEAD__FILE__
