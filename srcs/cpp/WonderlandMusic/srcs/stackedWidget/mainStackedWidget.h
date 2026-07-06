#ifndef MAINSTACKEDWIDGET_H_H_HEAD__FILE__
#define MAINSTACKEDWIDGET_H_H_HEAD__FILE__

#include <QStackedWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class MusicContreWidget;
class PlayerToolsWidget;
class FavoriteWidget;
class PlayerListTopWidget;
class AboutWidget;
class SettingWidget;
class PlayerWindow;

class MainStackedWidget : public QStackedWidget, public IAppCore, public IAppJsonData {
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
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual PlayerWindow * getPlayerWindow( ) const;

	virtual SettingWidget * getSettingWidget( ) const;

	virtual AboutWidget * getAboutWidget( ) const;

public Q_SLOTS:
	void slot_showPlayerWidget( );

	void slot_showSettingWidget( );

	void slot_showAboutWidget( );
};

#endif // MAINSTACKEDWIDGET_H_H_HEAD__FILE__
