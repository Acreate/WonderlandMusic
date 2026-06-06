#ifndef FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__
#define FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
class FunctionWidgetEventInfo;
class FunctionWidget;
class MainWindow;
/// @brief 功能面板
class FunctionDockWidget : public QDockWidget {
	friend class FunctionWidgetEvent;
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	FunctionWidget *functionWidget;
public:
	FunctionDockWidget( MainWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
private:
	virtual size_t triggerFunctionWidgetEvent( FunctionWidget *sender_function_widget, const FunctionWidgetEventInfo &function_widget_event_info );
};

class FunctionDockEventInfo {
public:
	enum class EventType {
		None,
		Show_Music,
		Show_Setting,
	};
protected:
	EventType type;
public:
	virtual ~FunctionDockEventInfo( ) = default;
	FunctionDockEventInfo( const EventType type )
		: type( type ) { }
	virtual EventType getType( ) const { return type; }
};
class FunctionWidgetEvent {
	friend class FunctionWidget;
	static size_t triggerTopToolEvent( FunctionDockWidget *receive_top_tool_dock_widget, FunctionWidget *sender_function_widget, const FunctionWidgetEventInfo &function_widget_event_info ) {
		return receive_top_tool_dock_widget->triggerFunctionWidgetEvent( sender_function_widget, function_widget_event_info );
	}
};
#endif // FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__
