#ifndef PLAYERWINDOW_H_H_HEAD__FILE__
#define PLAYERWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../application/appDiskJsonData.h"
#include "../application/appTranslate.h"
class FavoritemDockWidget;
class MusicContreWidget;
class MusicControlDocWidget;
class MusicItemSizeInfoDockWidget;
class FavoriteWidget;
class UserMutex;
class MusicInfoItemWidget;
class PlayerListWidgetMenu;
class QStackedWidget;
class PlayerToolsWidget;
class PlayerListTopWidget;
class QScrollArea;
class PlayerListWidget;

class PlayerWindow : public QMainWindow, public AppCore, public AppDiskJsonData {
	Q_OBJECT;

protected:
	/// @brief 收藏夹组件容器
	FavoritemDockWidget *favoritemDockWidget = nullptr;
	/// @brief 列表选项宽度组件容器
	MusicItemSizeInfoDockWidget *musicItemSizeInfoDockWidget = nullptr;
	/// @brief 音频播放选项组件容器
	MusicControlDocWidget *musicControlDocWidget = nullptr;
	/// @brief 音频列表枚举组件容器
	MusicContreWidget *musicContreWidget = nullptr;

protected:
	bool deleteResource( ) override;

	virtual bool initWidget( );

	virtual bool initMenu( );

	virtual bool initConnect( );

	virtual bool updateSubCompoment( );

	bool readJsonData( ) override;

	bool writeJsonData( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	~PlayerWindow( ) override;

	PlayerWindow( QWidget *parent );

	bool init( ) override;
};

#endif // PLAYERWINDOW_H_H_HEAD__FILE__
