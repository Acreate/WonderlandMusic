#ifndef FUNCTIONWIDGET_H_H_HEAD__FILE__
#define FUNCTIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>
#include <macro/eventMacroDefine.h>

#include "../../../baseWidget/baseWidget.h"
class QPushButton;
class FunctionDockWidget;
class FunctionWidget : public BaseWidget {
	Q_OBJECT;
protected:
	FunctionDockWidget *functionDockWidget;
	QPushButton *showMusicBtn;
	QPushButton *showSettingBtn;
public:
	FunctionWidget( FunctionDockWidget *parent );
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#define FunctionWidgetEventTypeName Event_Default_Event_Info_Type_Name( FunctionWidget )
class FunctionWidgetEventTypeName {
public:
	enum class EventType {
		None,
		Show_Music,
		Show_Setting
	};
protected:
	EventType eventType;
public:
	virtual ~FunctionWidgetEventTypeName( ) = default;
	FunctionWidgetEventTypeName( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // FUNCTIONWIDGET_H_H_HEAD__FILE__
