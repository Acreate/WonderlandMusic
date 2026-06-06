#ifndef FUNCTIONWIDGET_H_H_HEAD__FILE__
#define FUNCTIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class QPushButton;
class FunctionDockWidget;
class FunctionWidget : public QWidget {
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

class FunctionWidgetEventInfo {
public:
	enum class EventType {
		None,
		Show_Music,
		Show_Setting
	};
protected:
	EventType eventType;
public:
	virtual ~FunctionWidgetEventInfo( ) = default;
	FunctionWidgetEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // FUNCTIONWIDGET_H_H_HEAD__FILE__
