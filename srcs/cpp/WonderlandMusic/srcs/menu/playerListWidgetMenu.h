#ifndef PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__
#define PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__
#include <QMenu>
#include "../interface/iAppCore.h"
class FavoriteItem;

class PlayerListWidgetMenu : public QMenu, public IAppCore {
	Q_OBJECT;

protected:
	/// @brief 加载菜单
	QMenu *loadMusicMenu;
	/// @brief 删除菜单
	QMenu *removeMusicMenu;
	/// @brief 聚合菜单
	QMenu *aggregateMusicMenu;
	/// @brief 排序菜单
	QMenu *sortMusicMenu;
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
	/// @brief 添加选择文件到集
	QAction *opendSelectFileDialogAction;
	/// @brief 添加选择目录到集
	QAction *openSelectDirDialogAction;
	/// @brief 聚合到首选项
	QAction *aggregateToSelectFirst;
	/// @brief 聚合到末选项
	QAction *aggregateToSelectLast;
	/// @brief 选择的收藏夹所在项
	FavoriteItem *selectItem = nullptr;

protected:
	bool deleteResource( ) override;

public:
	virtual FavoriteItem * getSelectItem( ) const;

	virtual void setSelectItem( FavoriteItem *const select_item );
	PlayerListWidgetMenu( );
	~PlayerListWidgetMenu( ) override;
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
Q_SIGNALS:
	void signal_open_file_dialog( );
	void signal_open_dir_dialog( );
	void signal_select_move_top( );
	void signal_select_move_bottom( );
	void signal_select_aggregate_select_first( );
	void signal_select_aggregate_select_last( );
	void signal_select_aggregate_play_before( );
	void signal_select_aggregate_play_after( );
	void signal_select_music_remove_list( );
	void signal_select_music_delete_file_list( );
};
#endif // PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__
