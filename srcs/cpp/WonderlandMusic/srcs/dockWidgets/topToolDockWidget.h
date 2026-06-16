#ifndef TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
#define TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__

#include <macro/eventMacroDefine.h>
#include <base/baseWidget/baseDockWidget.h>

class TopToolWidgetEventInfo;
class TopToolWidget;
class MainWindow;
class TopToolDockWidget : public BaseDockWidget {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	TopToolWidget *topToolWidget;
public:
	TopToolDockWidget( MainWindow *parent );
};

#define TopToolDockWidgetEventTypeName Event_Define_Event_Info_Type_Name( TopToolDockWidget )
#define TopToolWidgetEventTypeName Event_Define_Event_Info_Type_Name( TopToolWidget )
class TopToolDockWidgetEventTypeName {
	friend class TopToolDockWidget;
public:
	enum class EventType {
		None,
		TopToolEvent
	};
protected:
	EventType eventType = EventType::None;
public:
	TopToolDockWidgetEventTypeName( ) { }
	virtual ~TopToolDockWidgetEventTypeName( ) = default;
	virtual EventType getEventType( ) const { return eventType; }
};

#endif // TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
