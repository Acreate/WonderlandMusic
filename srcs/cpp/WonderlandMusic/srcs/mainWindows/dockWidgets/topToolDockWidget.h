#ifndef TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
#define TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
#include <event/eventMacroDefine.h>

class TopToolWidget;
class MainWindow;

#define TopToolWidgetEventClassName Event_Default_ClassName( TopToolWidget )
#define TopToolWidgetEventDefaultEventCallFunction Event_Default_Receive_Call_Function(TopToolWidget)
#define TopToolWidgetEventDefineClass Event_Define_Event_Class_type( TopToolWidget, TopToolDockWidget )

class Event_Default_Event_Info_Type_Name( TopToolWidget );

class TopToolDockWidget : public QDockWidget {
	friend class TopToolWidgetEventClassName;
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	TopToolWidget *topToolWidget;
public:
	TopToolDockWidget( MainWindow *parent );
private:
	virtual TopToolWidgetEventDefaultEventCallFunction;
};

#define TopToolDockWidgetEventTypeName Event_Default_Event_Info_Type_Name( TopToolDockWidget )
#define TopToolWidgetEventTypeName Event_Default_Event_Info_Type_Name( TopToolWidget )
class TopToolDockWidgetEventTypeName {
	friend class TopToolDockWidget;
public:
	enum class EventType {
		None,
		TopToolEvent
	};
	class TopToolEventData {
		TopToolWidget *sender_top_tool_widget;
		const TopToolWidgetEventTypeName *top_tool_event_info;
	public:
		virtual ~TopToolEventData( ) = default;
		TopToolEventData( ::TopToolWidget *const sender_top_tool_widget, const ::TopToolWidgetEventTypeName *const top_tool_event_info )
			: sender_top_tool_widget( sender_top_tool_widget ),
			top_tool_event_info( top_tool_event_info ) { }
		virtual TopToolWidget * getSenderTopToolWidget( ) const { return sender_top_tool_widget; }
		virtual const TopToolWidgetEventTypeName * getTopToolEventInfo( ) const { return top_tool_event_info; }
	};
protected:
	EventType eventType = EventType::None;
	TopToolEventData *topToolEventData = nullptr;
public:
	TopToolDockWidgetEventTypeName( ) { }
	virtual ~TopToolDockWidgetEventTypeName( ) = default;
	virtual EventType getEventType( ) const { return eventType; }
	virtual TopToolEventData * getTopToolEventData( ) const { return topToolEventData; }
};

TopToolWidgetEventDefineClass;

#endif // TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
