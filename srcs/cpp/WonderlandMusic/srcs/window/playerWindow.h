#ifndef PLAYERWINDOW_H_H_HEAD__FILE__
#define PLAYERWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../application/appJsonData.h"
#include "../application/appTranslate.h"
class UserMutex;
class MusicInfoItemWidget;
class PlayerListWidgetMenu;
class QStackedWidget;
class PlayerToolsWidget;
class PlayerListTopWidget;
class QScrollArea;
class PlayerListWidget;

class PlayerWindow : public QMainWindow, public AppCore, public AppJsonData {
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
	/// @brief 列表菜单
	PlayerListWidgetMenu *playerListWidgetMenu = nullptr;
	/// @brief 当前菜单
	PlayerListWidget *currentPlayerListWidget = nullptr;
	/// @brief 播放列表层级菜单
	QStackedWidget *playerListStackedWidget = nullptr;
	/// @brief 文件选择工作路径
	QString fileSelectWorkPath;
	/// @brief 目录选择工作路径
	QString dirSelectWorkPath;
	/// @brief 音乐加载列表锁
	UserMutex *musicInfoMutex = nullptr;
	/// @brief 音乐加载列表
	std::vector< MusicInfoItemWidget * > musicInfoVector;

protected:
	bool deleteResource( ) override;

	virtual bool initWidget( );

	virtual bool initMenu( );

	virtual bool initConnect( );

	virtual bool updateSubCompoment( );

	virtual bool popPlayerListWidgetMenu( );

	bool readJsonData( ) override;

	bool writeJsonData( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	~PlayerWindow( ) override;

	PlayerWindow( QWidget *parent );

	bool init( ) override;

	virtual PlayerListWidget * getPlayListWidget( ) const;

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const;

	virtual PlayerToolsWidget * getPlayerToolsWidget( ) const;

	virtual PlayerListWidgetMenu * getPlayerListWidgetMenu( ) const;

protected:
	void showEvent( QShowEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // PLAYERWINDOW_H_H_HEAD__FILE__
