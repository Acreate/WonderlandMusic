#ifndef PLAYERWINDOW_H_H_HEAD__FILE__
#define PLAYERWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../application/appTranslate.h"

#include "../interface/iAppJsonData.h"

class MusicListWindow;
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

class PlayerWindow : public QMainWindow, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	/// @brief 收藏夹组件容器
	FavoritemDockWidget *favoritemDockWidget = nullptr;
	/// @brief 音乐列表组件
	MusicListWindow *musicListWindow = nullptr;
	/// @brief 音频播放选项组件容器
	MusicControlDocWidget *musicControlDocWidget = nullptr;

protected:
	bool deleteResource( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	~PlayerWindow( ) override;

	PlayerWindow( QWidget *parent );

	virtual FavoritemDockWidget * getFavoritemDockWidget( ) const;

	virtual MusicListWindow * getMusicListWindow( ) const;

	virtual MusicControlDocWidget * getMusicControlDocWidget( ) const;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;
};

#endif // PLAYERWINDOW_H_H_HEAD__FILE__
