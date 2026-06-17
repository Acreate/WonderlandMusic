#ifndef PLAYERWINDOW_H_H_HEAD__FILE__
#define PLAYERWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
class PlayerListTopWidget;
class QScrollArea;
class PlayListWidget;

class PlayerWindow : public QMainWindow {
	Q_OBJECT;

protected:
	/// @brief 播放列表的滚动容器
	QScrollArea *playListWidgetScrollArea;
	/// @brief 在层叠组件配置播放组件
	PlayListWidget *playListWidget;
	/// @brief 文件选择工作路径
	QString fileSelectWorkPath;
	/// @brief 目录选择工作路径
	QString dirSelectWorkPath;
	/// @brief 顶部容器
	QDockWidget *topDocWidget;
	/// @brief 播放的顶部组件
	PlayerListTopWidget *playerListTopWidget;

public:
	PlayerWindow( QWidget *parent );

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );
};

#endif // PLAYERWINDOW_H_H_HEAD__FILE__
