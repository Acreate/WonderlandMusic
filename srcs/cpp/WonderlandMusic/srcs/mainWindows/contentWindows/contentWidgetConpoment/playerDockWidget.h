#ifndef PLAYERDOCKWIDGET_H_H_HEAD__FILE__
#define PLAYERDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
class QPushButton;
class ContentWindow;

class PlayerDockWidget : public QDockWidget {
	Q_OBJECT;
public:
	/// @brief 播放状态
	enum class ControlStatus {
		None,
		Player,
		Pause,
	};
protected:
	ContentWindow *contentWindow;
	/// @brief 上一曲
	QPushButton *previousTrackBtn;
	/// @brief 控制当前播放
	QPushButton *controlCurrentBtn;
	/// @brief 下一曲
	QPushButton *nextTrackBtn;
	/// @brief 
	ControlStatus controlStatus;
public:
	PlayerDockWidget( ContentWindow *parent );
};

#include <event/eventMacroDefine.h>
#define PlayerDockWidgetEventTypeName Event_Default_Event_Info_Type_Name( PlayerDockWidget )
class PlayerDockWidgetEventTypeName {
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
	virtual ~PlayerDockWidgetEventInfo( ) = default;
	PlayerDockWidgetEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // PLAYERDOCKWIDGET_H_H_HEAD__FILE__
