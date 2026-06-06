#ifndef CONTENTWINDOW_H_H_HEAD__FILE__
#define CONTENTWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
#include <event/eventMacroDefine.h>
class CoreInfo;
class CoreWindow;
class PlayerInfo;
class FindInfo;
class MainWindow;
class FindDockWidget;
class PlayerDockWidget;

#define FindEventClassName Event_Default_ClassName( Find )
#define FindEventTrigger Event_Default_Event_Call_Function_Name(  Find )
#define FindEventDefineClass Event_Define_Event_Class_type( Find, ContentWindow, FindDockWidget, FindInfo )

#define PlayerEventClassName Event_Default_ClassName( Player )
#define PlayerEventTrigger Event_Default_Event_Call_Function_Name(  Player )
#define PlayerEventDefineClass Event_Define_Event_Class_type( Player, ContentWindow, PlayerDockWidget, PlayerInfo )

#define CoreWindowEventClassName Event_Default_ClassName( CoreWindow )
#define CoreWindowEventTrigger Event_Default_Event_Call_Function_Name(  CoreWindow )
#define CoreWindowEventDefineClass Event_Define_Event_Class_type( CoreWindow, ContentWindow, CoreWindow, CoreInfo )

/// @brief 内容窗口
class ContentWindow : public QMainWindow {
	friend class FindEventClassName;
	friend class PlayerEventClassName;
	friend class CoreWindowEvent;
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
private:
	virtual size_t FindEventTrigger( FindDockWidget *sender_find_dock_widget, const FindInfo &find_info ) {
		return 0;
	}
	virtual size_t PlayerEventTrigger( PlayerDockWidget *sender_player_dock_widget, const PlayerInfo &player_info ) {
		return 0;
	}
	virtual size_t CoreWindowEventTrigger( CoreWindow *sender_player_dock_widget, const CoreInfo &player_info ) {
		return 0;
	}
};
FindEventDefineClass;
PlayerEventDefineClass;
CoreWindowEventDefineClass;

#endif // CONTENTWINDOW_H_H_HEAD__FILE__
