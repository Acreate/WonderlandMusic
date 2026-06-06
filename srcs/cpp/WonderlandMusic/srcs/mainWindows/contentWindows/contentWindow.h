#ifndef CONTENTWINDOW_H_H_HEAD__FILE__
#define CONTENTWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
#include <macro/eventMacroDefine.h>
class CoreInfo;
class CoreWindow;
class PlayerInfo;
class FindInfo;
class MainWindow;
class FindDockWidget;
class PlayerDockWidget;

#define FindEventClassName Event_Default_Event_Class_Type_Name( FindDockWidget )
#define FindEventDefaultEventCallFunction Event_Default_Receive_Call_Function(FindDockWidget)
#define FindEventDefineClass Event_Define_Event_Class_type( FindDockWidget, ContentWindow )
class Event_Default_Event_Info_Type_Name( FindDockWidget );

#define PlayerEventClassName Event_Default_Event_Class_Type_Name( PlayerDockWidget )
#define PlayerEventDefaultEventCallFunction Event_Default_Receive_Call_Function(PlayerDockWidget )
#define PlayerEventDefineClass Event_Define_Event_Class_type( PlayerDockWidget, ContentWindow)
class Event_Default_Event_Info_Type_Name( PlayerDockWidget );

#define CoreWindowEventClassName Event_Default_Event_Class_Type_Name( CoreWindow )
#define CoreWindowDefaultEventCallFunction Event_Default_Receive_Call_Function(CoreWindow)
#define CoreWindowEventDefineClass Event_Define_Event_Class_type( CoreWindow, ContentWindow )
class Event_Default_Event_Info_Type_Name( CoreWindow );

/// @brief 内容窗口
class ContentWindow : public QMainWindow {
	friend class FindEventClassName;
	friend class PlayerEventClassName;
	friend class CoreWindowEventClassName;
	Q_OBJECT;
protected:
	/// @brief 父节点
	MainWindow *mainWindow;
	/// @brief 查找窗口
	FindDockWidget *findDockWidget;
	/// @brief 播放窗口
	PlayerDockWidget *playerDockWidget;
	/// @brief 核心窗口
	CoreWindow *coreWindow;
public:
	ContentWindow( MainWindow *parent );
	/// @brief 显示音乐面板
	/// @return 失败返回 false
	virtual bool showMusicWidget( );
	/// @brief 显示设置面板
	/// @return 失败返回 false
	virtual bool showSettingWidget( );
private:
	virtual FindEventDefaultEventCallFunction;
	virtual PlayerEventDefaultEventCallFunction;
	virtual CoreWindowDefaultEventCallFunction;
};

#define ContentWindowEventTypeName Event_Default_Event_Info_Type_Name( ContentWindow )
class ContentWindowEventTypeName {
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
	virtual ~ContentWindowEventTypeName( ) = default;
	ContentWindowEventTypeName( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};

FindEventDefineClass;
PlayerEventDefineClass;
CoreWindowEventDefineClass;

#endif // CONTENTWINDOW_H_H_HEAD__FILE__
