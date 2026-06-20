#ifndef PLAYERWIDGETMENU_H_H_HEAD__FILE__
#define PLAYERWIDGETMENU_H_H_HEAD__FILE__

#include <QMenu>
class PlayerListMenuTranslate;
class MusicDecoder;
class AppTranslate;
class AppInstance;
class MusicInfoItemWidget;
class PlayerListWidget;

class PlayerWidgetMenu : public QMenu {
	Q_OBJECT;

protected:
	AppInstance *appInstance;
	const AppTranslate *appTranslate;
	PlayerListMenuTranslate *playerListMenuTranslate;
	MusicDecoder *musicDecoder;
	/// @brief 文件选择工作路径
	QString fileSelectWorkPath;
	/// @brief 目录选择工作路径
	QString dirSelectWorkPath;
	PlayerListWidget *playerListWidget;
	QVector< MusicInfoItemWidget * > musicInfoItemWidgetVector;
	/// @brief 播放菜单
	QMenu *playerMenu;
	/// @brief 删除菜单
	QMenu *removeMenu;
	/// @brief 控制菜单
	QMenu *controlMenu;
	/// @brief 插入当前播放列表
	QAction *insterPlay;
	/// @brief 播放当前列表
	QAction *setplay;
	/// @brief 移动到顶部
	QAction *moveTop;
	/// @brief 移动到底部
	QAction *moveBottom;
	/// @brief 移除选中
	QAction *removeMusic;
	/// @brief 删除选中
	QAction *deleteMusic;
	/// @brief 加载菜单
	QMenu *loadMenu;
	/// @brief 添加选择文件到集
	QAction *addMultiFileMusicToCollectionAction;
	/// @brief 添加选择目录到集
	QAction *addMultiMusicDirToCollection;

public:
	PlayerWidgetMenu( PlayerListWidget *player_list_widget );

	virtual bool initVar( );

	virtual bool initSubMenu( );

	virtual bool initSubMenuAcction( );

	virtual bool initConnectAcction( );

	virtual bool init( );

protected:
	void setCurrentSelectPlay( );

	void insterCurrentSelectPlay( );

	void removePlayListSelectInfo( );

	void deletePlayListSelectFile( );

	void selectListMoveTop( );

	void selectListMoveBottom( );
};

#endif // PLAYERWIDGETMENU_H_H_HEAD__FILE__
