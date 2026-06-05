#ifndef CONTENTWINDOW_H_H_HEAD__FILE__
#define CONTENTWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
class CoreInfo;
class CoreWindow;
class PlayerInfo;
class FindInfo;
class MainWindow;
class FindDockWidget;
class PlayerDockWidget;
/// @brief 内容窗口
class ContentWindow : public QMainWindow {
	friend class FindEvent;
	friend class PlayerEvent;
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
protected:
	void paintEvent( QPaintEvent *event ) override;
private:
	virtual size_t triggerFindEvent( FindDockWidget *sender_find_dock_widget, const FindInfo &find_info ) {
		return 0;
	}
	virtual size_t triggerPlayerEvent( PlayerDockWidget *sender_player_dock_widget, const PlayerInfo &player_info ) {
		return 0;
	}
	virtual size_t triggerCoreWindowEvent( CoreWindow *sender_player_dock_widget, const CoreInfo &player_info ) {
		return 0;
	}
};

class FindEvent {
	friend class FindDockWidget;
	static size_t triggerFindEvent( ContentWindow *receive_content_window, FindDockWidget *sender_find_dock_widget, const FindInfo &find_info ) {
		return receive_content_window->triggerFindEvent( sender_find_dock_widget, find_info );
	}
};

class PlayerEvent {
	friend class PlayerDockWidget;
	static size_t triggerPlayerEvent( ContentWindow *receive_content_window, PlayerDockWidget *sender_player_dock_widget, const PlayerInfo &player_info ) {
		return receive_content_window->triggerPlayerEvent( sender_player_dock_widget, player_info );
	}
};

class CoreWindowEvent {
	friend class PlayerDockWidget;
	static size_t triggerCoreWindowEvent( ContentWindow *receive_content_window, CoreWindow *sender_core_window, const CoreInfo &core_info ) {
		return receive_content_window->triggerCoreWindowEvent( sender_core_window, core_info );
	}
};

#endif // CONTENTWINDOW_H_H_HEAD__FILE__
