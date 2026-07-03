#ifndef MUSICLISTWINDOW_H_H_HEAD__FILE__
#define MUSICLISTWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../interface/iAppCore.h"

class MusicItem;
class MusicContreScrollArea;
class MusicListStackedWidget;
class PlayerListTopWidget;
class MusicContreWidget;
class MusicItemSizeInfoDockWidget;

class MusicListWindow : public QMainWindow, public IAppCore {
	Q_OBJECT;

protected:
	/// @brief 列表选项宽度组件容器
	MusicItemSizeInfoDockWidget *musicItemSizeInfoDockWidget = nullptr;

	/// @brief 音频列表枚举组件容器
	MusicListStackedWidget *musicListStackedWidget = nullptr;
	/// @brief 滚动视图序列
	std::vector< MusicContreScrollArea * > musicContreScrollAreaVector;

protected:
	virtual MusicContreScrollArea * findWidgetName( const QString &widget_name ) const;

public:
	MusicListWindow( QWidget *parent );

	~MusicListWindow( ) override;

	virtual bool showWidget( const QString &widget_name );

	virtual bool createWidget( const QString &widget_name, const std::vector< MusicItem * > &load_music_items );

	virtual PlayerListTopWidget * getPlayerListTopWidget( ) const;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;
};

#endif // MUSICLISTWINDOW_H_H_HEAD__FILE__
