#ifndef PLAYERWIDGETMENU_H_H_HEAD__FILE__
#define PLAYERWIDGETMENU_H_H_HEAD__FILE__

#include <QMenu>
class AppTranslate;
class AppInstance;
class MusicInfoItemWidget;
class PlayerListWidget;

class PlayerWidgetMenu : public QMenu {
	Q_OBJECT;

protected:
	AppInstance *appInstance;
	const AppTranslate *appTranslate;
	PlayerListWidget *playerListWidget;
	QVector< MusicInfoItemWidget * > musicInfoItemWidgetVector;
	/// @brief 播放菜单
	QMenu *playerMenu;
	/// @brief 控制菜单
	QMenu *controlMenu;
	/// @brief 插入当前播放列表
	QAction *insterCurrentSelectToPlayerList;
	/// @brief 播放当前列表
	QAction *setCurrentSelectToPlayerList;

public:
	PlayerWidgetMenu( PlayerListWidget *player_list_widget );
	virtual bool initVar();
	virtual bool initSubMenu( );

	virtual bool initSubMenuAcction( );

	virtual bool initConnectAcction( );

	virtual bool init( );
};

#endif // PLAYERWIDGETMENU_H_H_HEAD__FILE__
