#ifndef PLAYERWIDGET_H_H_HEAD__FILE__
#define PLAYERWIDGET_H_H_HEAD__FILE__

#include <macro/eventMacroDefine.h>

#include <base/baseWidget/baseWidget.h>

class ApplicationEvenTrigger;
class ApplicationInstance;
class QPushButton;
class PlayerDockWidget;
class PlayerWidget : public BaseWidget {
	Q_OBJECT;
public:
	/// @brief 播放状态
	enum class ControlStatus {
		None,
		Player,
		Pause,
	};
protected:
	PlayerDockWidget *playerDockWidget;
	/// @brief 上一曲
	QPushButton *previousTrackBtn;
	/// @brief 控制当前播放
	QPushButton *controlCurrentBtn;
	/// @brief 下一曲
	QPushButton *nextTrackBtn;
	/// @brief 
	ControlStatus controlStatus;
public:
	PlayerWidget( PlayerDockWidget *parent );
};

class Event_Define_Event_Info_Type_Name( PlayerWidget ) {
public:
	enum class EventType {
		None,
		Player,
		Pause,
		Next_Track,
		Previous_Track,
	};
protected:
	EventType eventType;
public:
	virtual ~PlayerWidgetEventInfo( ) = default;
	PlayerWidgetEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // PLAYERWIDGET_H_H_HEAD__FILE__
