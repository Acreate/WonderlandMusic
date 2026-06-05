#ifndef TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
#define TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
class TopToolEventInfo;
class TopToolEvent;
class TopToolWidget;
class MainWindow;
class TopToolDockWidget : public QDockWidget {
	friend class TopToolEvent;
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	TopToolWidget *topToolWidget;
public:
	TopToolDockWidget( MainWindow *parent );
private:
	virtual size_t triggerTopToolEvent( TopToolWidget *sender_top_tool_widget, const TopToolEventInfo &top_tool_event_info );
};

class TopToolDockEventInfo {
	friend class TopToolDockWidget;
public:
	enum class EventType {
		None,
		TopToolEvent
	};
	class TopToolEventData {
		TopToolWidget *sender_top_tool_widget;
		const TopToolEventInfo *top_tool_event_info;
	public:
		virtual ~TopToolEventData( ) = default;
		TopToolEventData( ::TopToolWidget *const sender_top_tool_widget, const ::TopToolEventInfo *const top_tool_event_info )
			: sender_top_tool_widget( sender_top_tool_widget ),
			top_tool_event_info( top_tool_event_info ) { }
		virtual TopToolWidget * getSenderTopToolWidget( ) const { return sender_top_tool_widget; }
		virtual const TopToolEventInfo * getTopToolEventInfo( ) const { return top_tool_event_info; }
	};
protected:
	EventType eventType = EventType::None;
	TopToolEventData *topToolEventData = nullptr;
public:
	TopToolDockEventInfo( ) { }
	virtual ~TopToolDockEventInfo( ) = default;
	virtual EventType getEventType( ) const { return eventType; }
	virtual TopToolEventData * getTopToolEventData( ) const { return topToolEventData; }
};

class TopToolEvent {
	friend class TopToolWidget;
	static size_t triggerTopToolEvent( TopToolDockWidget *receive_top_tool_dock_widget, TopToolWidget *sender_top_tool_widget, const TopToolEventInfo &top_tool_event_info ) {
		return receive_top_tool_dock_widget->triggerTopToolEvent( sender_top_tool_widget, top_tool_event_info );
	}
};
#endif // TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
