#ifndef MUSICLISTWINDOW_H_H_HEAD__FILE__
#define MUSICLISTWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class MusicItem;
class MusicContreScrollArea;
class MusicListStackedWidget;
class PlayerListTopWidget;
class MusicContreWidget;
class MusicItemSizeInfoDockWidget;

class MusicListWindow : public QMainWindow, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	/// @brief 列表选项宽度组件容器
	MusicItemSizeInfoDockWidget *musicItemSizeInfoDockWidget = nullptr;

	/// @brief 滚动音频列表组件容器
	MusicContreScrollArea *musicContreScrollArea = nullptr;

public:
	MusicListWindow( QWidget *parent );

	~MusicListWindow( ) override;

	virtual bool showFavorteMusicContreList( const QString &music_favorte_widget );

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const;
	virtual MusicContreWidget * getMusicContreWidget( ) const;

protected:
	bool deleteResource( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;
};

#endif // MUSICLISTWINDOW_H_H_HEAD__FILE__
