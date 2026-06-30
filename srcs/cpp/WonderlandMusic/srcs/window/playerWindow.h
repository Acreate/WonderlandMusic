#ifndef PLAYERWINDOW_H_H_HEAD__FILE__
#define PLAYERWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../application/appTranslate.h"
class PlayerWidgetMenu;
class PlayerToolsWidget;
class PlayerListTopWidget;
class QScrollArea;
class PlayerListWidget;

class PlayerWindow : public QMainWindow, public AppCore {
	Q_OBJECT;

protected:
	/// @brief 播放列表的滚动容器
	QScrollArea *playListWidgetScrollArea;
	/// @brief 在层叠组件配置播放组件
	PlayerListWidget *playListWidget;
	/// @brief 顶部容器
	QDockWidget *topDocWidget = nullptr;
	/// @brief 播放的顶部组件的滚动容器
	QScrollArea *playerListTopWidgetScrollArea;
	/// @brief 播放的顶部组件
	PlayerListTopWidget *playerListTopWidget;

	/// @brief 底部容器
	QDockWidget *bottomDocWidget = nullptr;
	/// @brief 播放功能面板
	PlayerToolsWidget *playerToolsWidget;
	/// @brief 播放列表菜单
	PlayerWidgetMenu *playerWidgetMenu = nullptr;

protected:
	bool deleteResource( ) override;

	virtual bool initWidget( );

	virtual bool initMenu( );

	virtual bool initConnect( );

	virtual bool updateSubCompoment( );

	virtual bool popPlayerWidgetMenu( );

public:
	~PlayerWindow( ) override;

	PlayerWindow( QWidget *parent );

	bool init( ) override;

protected:
	void showEvent( QShowEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // PLAYERWINDOW_H_H_HEAD__FILE__
