#ifndef MAINSTACKEDWIDGET_H_H_HEAD__FILE__
#define MAINSTACKEDWIDGET_H_H_HEAD__FILE__

#include <QStackedWidget>

#include "../interface/iAppCore.h"

class MusicContreWidget;
class PlayerToolsWidget;
class FavoriteWidget;
class PlayerListTopWidget;
class AboutWidget;
class SettingWidget;
class PlayerWindow;

class MainStackedWidget : public QStackedWidget, public IAppCore {
	Q_OBJECT;

protected:
	/// @brief 播放窗口
	PlayerWindow *playerWindow = nullptr;
	/// @brief 在层叠组件配置设置组件
	SettingWidget *settingWidget = nullptr;
	/// @brief 在层叠组件配置关于组件
	AboutWidget *aboutWidget = nullptr;

public:
	MainStackedWidget( QWidget *parent );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const;

	virtual FavoriteWidget * getFavoriteWidget( ) const;
	virtual MusicContreWidget * getMusicContreWidget( ) const;

public Q_SLOTS:
	void slot_showPlayerWidget( );

	void slot_showSettingWidget( );

	void slot_showAboutWidget( );
};

#endif // MAINSTACKEDWIDGET_H_H_HEAD__FILE__
