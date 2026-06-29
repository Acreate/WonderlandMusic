#ifndef PLAYERWIDGETMENU_H_H_HEAD__FILE__
#define PLAYERWIDGETMENU_H_H_HEAD__FILE__

#include <QMenu>

#include "../application/appCore.h"
class JsonFileKey;
class PlayerListMenuJsonKey;
class PlayerListMenuTranslate;
class MusicDecoder;
class AppTranslate;
class AppInstance;
class MusicInfoItemWidget;
class PlayerListWidget;

class PlayerWidgetMenu : public QMenu, public AppCore {
	Q_OBJECT;

protected:
	AppInstance *appInstance;
	const AppTranslate *appTranslate;
	PlayerListMenuTranslate *playerListMenuTranslate;
	MusicDecoder *musicDecoder;
	const JsonFileKey *jsonFileKey;
	PlayerListMenuJsonKey *playerListMenuJsonKey;
	PlayerListWidget *playerListWidget;
	QVector< MusicInfoItemWidget * > musicInfoItemWidgetVector;
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
	QAction *removeMusicAtList;
	/// @brief 删除选中
	QAction *deleteMusicAtDiskFile;
	/// @brief 加载菜单
	QMenu *loadMenu;
	/// @brief 添加选择文件到集
	QAction *addMultiFileMusicToCollectionAction;
	/// @brief 添加选择目录到集
	QAction *addMultiMusicDirToCollection;

protected:
	bool deleteResource( ) override;

public:
	PlayerWidgetMenu( PlayerListWidget *player_list_widget );

	bool init( ) override;

protected:
	virtual bool initVar( );

	virtual bool initSubMenu( );

	virtual bool initSubMenuAcction( );

	virtual bool initConnectAcction( );

	virtual void loadDiskFile( );

	virtual void loadDiskDir( );

	virtual void setCurrentSelectPlay( );

	virtual void insterCurrentSelectPlay( );

	virtual void removePlayListSelectInfo( );

	virtual void deletePlayListSelectFile( );

	virtual void selectListMoveTop( );

	virtual void selectListMoveBottom( );
};

#include <application/eventMacro/eventMacroDefault.h>
definition_event_info_class_type( PlayerWidgetMenu, Load_Disk_File, Load_Disk_Dir, Set_Current_Select_Play, Inster_Current_Select_Play, Remove_Play_List_Select_Info, Delete_Play_List_Select_File, Select_List_Move_Top, Select_List_Move_Bottom );

#endif // PLAYERWIDGETMENU_H_H_HEAD__FILE__
