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

/// @brief 内容窗口
class ContentWindow : public QMainWindow {
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

#endif // CONTENTWINDOW_H_H_HEAD__FILE__
