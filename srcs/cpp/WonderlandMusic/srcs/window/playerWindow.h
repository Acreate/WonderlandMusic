#ifndef PLAYERWINDOW_H_H_HEAD__FILE__
#define PLAYERWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../application/appTranslate.h"
class PlayerToolsWidget;
class PlayerListTopWidget;
class QScrollArea;
class PlayerListWidget;

class PlayerWindow : public QMainWindow {
	Q_OBJECT;

protected:
	/// @brief 播放列表的滚动容器
	QScrollArea *playListWidgetScrollArea;
	/// @brief 在层叠组件配置播放组件
	PlayerListWidget *playListWidget;
	/// @brief 文件选择工作路径
	QString fileSelectWorkPath;
	/// @brief 目录选择工作路径
	QString dirSelectWorkPath;
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
	/// @brief 工具菜单
	QMenuBar *windowMenuBar = nullptr;

	QAction *addMultiFileMusicToCollectionAction;
	QAction *addMultiMusicDirToCollection;
	QAction *removeMultiMusicItemAtCollectionAction;

protected:
	virtual void releaeseResource( );

	virtual bool initWidget( );

	virtual bool initMenuBar( );

	virtual bool initConnect( );

	virtual bool updateSubCompoment( );

public:
	~PlayerWindow( ) override;

	PlayerWindow( QWidget *parent );

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );

	virtual bool init( );

protected:
	void showEvent( QShowEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;
};

#endif // PLAYERWINDOW_H_H_HEAD__FILE__
