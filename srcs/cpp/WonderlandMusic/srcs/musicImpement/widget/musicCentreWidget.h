#ifndef MUSICCENTREWIDGET_H_H_HEAD__FILE__
#define MUSICCENTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>

class MusicScrollArea;
class IMusicWidget;
class IMusicDataManage;
class IMusicItemWidthInfo;
class IMusicWidgetSizeInfo;
class IMusicTitleWidget;
class IMusicListWidget;
class IMusicFavoriteWidget;
class IMusicListMenu;
class IMusicFavoriteMenu;
class TransparencyScrollBar;
class QScrollArea;
class UserMutex;
class MusicWindow;

class MusicCentreWidget : public QWidget, public IMusicCentreWidget {
	Q_OBJECT;
	friend class MusicCentreWidgetTools;

protected:
	enum class Drag_Status {
		None,
		MusicFavoriteWidget,
		MusicTitleWidget
	};

private:
	MusicWindow *musicWindow;
	UserMutex *userMutex = nullptr;
	MusicScrollArea *musicfavoriteWidgetScrollArea = nullptr;
	MusicScrollArea *musicTitleWidgetScrollArea = nullptr;
	MusicScrollArea *musicListWidgetScrollArea = nullptr;
	IMusicFavoriteWidget *musicFavoriteWidget = nullptr;
	IMusicListWidget *musicListWidget = nullptr;
	IMusicTitleWidget *musicTitleWidget = nullptr;
	IMusicDataManage *musicDataManage = nullptr;
	bool isOverMouseEvent = false;
	Qt::CursorShape cursorShape;
	Drag_Status dragStatus = Drag_Status::None;
	Drag_Status readDragStatus = Drag_Status::None;
	int clickWidth;
	int minWidth;
	int favoriteLeft;
	int favoriteRight;
	int favoriteWidth;
	int titleTop;
	int titleBottom;
	int titleHeight;
	bool isDrag = false;
	int dragOrgX = 0;
	int dragOrgY = 0;
	int dragOffsetX = 0;
	int dragOffsetY = 0;

public:
	MusicCentreWidget( );
	~MusicCentreWidget( ) override;

protected:
	bool deleteResource( ) override;
	void resizeEvent( QResizeEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
	bool setMusicWindow( MusicWindow *music_window ) override;

public:
	QWidget * toWidget( ) override;

protected:
	bool event( QEvent *event ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	MusicWindow * getMusicWindow( ) const override;
	IMusicFavoriteWidget * getMusicFavoriteWidget( ) const override;
	IMusicListWidget * getMusicListWidget( ) const override;
	IMusicTitleWidget * getMusicTitleWidget( ) const override;
	IMusicDataManage * getMusicDataManage( ) const override;
	IMusicFavoriteMenu * getMusicFavoriteMenu( ) const override;
	IMusicListMenu * getMusicListMenu( ) const override;
	IMusicWidgetSizeInfo * getMusicWidgetSizeInfo( ) const override;
	IMusicFavoriteWidget * setMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) override;
	IMusicListWidget * setMusicListWidget( IMusicListWidget *const music_list_widget ) override;
	IMusicTitleWidget * setMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) override;
	IMusicDataManage * setMusicDataManage( IMusicDataManage *const music_data_manage ) override;

	IMusicFavoriteWidget * removeMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) override;
	IMusicListWidget * removeMusicListWidget( IMusicListWidget *const music_list_widget ) override;
	IMusicTitleWidget * removeMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) override;

	bool repaintListWidget( ) override;
	bool repaintTitleWidget( ) override;
	bool repaintFavoriteWidget( ) override;
	bool repaintMusicCentreWidget( ) override;
	bool synchronizationChildrenWidgetSize( ) override;
};

#endif // MUSICCENTREWIDGET_H_H_HEAD__FILE__
