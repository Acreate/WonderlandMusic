#ifndef PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__
#define PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__

#include <QMenu>

#include "../interface/iAppCore.h"

class PlayerListWidgetMenu : public QMenu, public IAppCore {
	Q_OBJECT;

protected:
	/// @brief 删除菜单
	QMenu *removeMenu;
	/// @brief 控制菜单
	QMenu *controlMenu;
	/// @brief 插入当前播放列表
	QAction *insterPlayAfter;
	/// @brief 播放当前列表
	QAction *insterPlayBefore;
	/// @brief 移动到顶部
	QAction *moveTop;
	/// @brief 移动到底部
	QAction *moveBottom;
	/// @brief 移除选中
	QAction *removeMusicAtList;
	/// @brief 删除选中
	QAction *deleteMusicAtDiskFile;
	/// @brief 加载菜单
	QMenu *loadMenu;
	/// @brief 添加选择文件到集
	QAction *opendSelectFileDialogAction;
	/// @brief 添加选择目录到集
	QAction *oopenSelectDirDialogAction;
	/// @brief 聚合到首选项
	QAction *aggregateToSelectFirst;
	/// @brief 聚合到末选项
	QAction *aggregateToSelectLast;

protected:
	bool deleteResource( ) override;

public:
	PlayerListWidgetMenu( );

	~PlayerListWidgetMenu( ) override;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;
};
#endif // PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__
