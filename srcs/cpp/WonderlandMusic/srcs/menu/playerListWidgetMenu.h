#ifndef PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__
#define PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__

#include <QMenu>

#include "../interface/iAppCore.h"

class AppDataJsonKey;
class AppMusicDecoder;
class PlayerListWidgetMenuTranlate;
class PlayerListMenuJsonKey;
class AppTranslate;
class AppInstance;
class MusicInfoItemWidget;
class PlayerListWidget;

class PlayerListWidgetMenu : public QMenu, public IAppCore {
	Q_OBJECT;

protected:
	AppInstance *appInstance;
	const AppTranslate *appTranslate;
	PlayerListWidgetMenuTranlate *playerListWidgetMenuTranlate;
	AppMusicDecoder *musicDecoder;
	const AppDataJsonKey *jsonFileKey;
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
	PlayerListWidgetMenu( );

	bool init( ) override;

protected:
	virtual bool initVar( );

	virtual bool initSubMenu( );

	virtual bool initSubMenuAcction( );

	virtual bool initConnectAcction( );

Q_SIGNALS:
	void loadDiskFile( );

	void loadDiskDir( );

	void setCurrentSelectPlay( );

	void insterCurrentSelectPlay( );

	void removePlayListSelectInfo( );

	void deletePlayListSelectFile( );

	void selectListMoveTop( );

	void selectListMoveBottom( );
};
#endif // PLAYERLISTWIDGETMENU_H_H_HEAD__FILE__
