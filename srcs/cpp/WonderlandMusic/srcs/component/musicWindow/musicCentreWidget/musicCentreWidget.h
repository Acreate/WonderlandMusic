#ifndef MUSICCENTREWIDGET_H_H_HEAD__FILE__
#define MUSICCENTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class MusicListMenu;
class MusicFavoriteMenu;
class MusicItem;
class TransparencyScrollBar;
class QScrollArea;
class MusicListWidget;
class UserMutex;
class MusicFavoriteWidget;
class MusicToolWidget;
class MusicTitleWidget;
class MusicWindow;

class MusicCentreWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicTitleWidgetTools;

private:
	MusicWindow *musicWindow;
	UserMutex *userMutex = nullptr;
	MusicFavoriteMenu *musicFavoriteMenu = nullptr;
	MusicListMenu *musicListMenu = nullptr;
	QScrollArea *musicfavoriteWidgetScrollArea = nullptr;
	QScrollArea *musicTitleWidgetScrollArea = nullptr;
	QScrollArea *musicListWidgetScrollArea = nullptr;
	MusicFavoriteWidget *musicfavoriteWidget = nullptr;
	MusicTitleWidget *musicTitleWidget = nullptr;
	MusicListWidget *musicListWidget = nullptr;
	MusicToolWidget *musicToolWidget = nullptr;

public:
	MusicCentreWidget( MusicWindow *parent );
	~MusicCentreWidget( ) override;

protected:
	bool deleteResource( ) override;
	void resizeEvent( QResizeEvent *event ) override;
	virtual QScrollArea * createControlScrollArea( QWidget *widget );

	virtual void updateTitleWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual void clearShowMusic( );
	virtual bool calculateSize( );
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual MusicWindow * getMusicWindow( ) const;
	virtual MusicFavoriteWidget * getMusicFavoriteWidget( ) const;
	virtual MusicTitleWidget * getMusicTitleWidget( ) const;
	virtual MusicListWidget * getMusicListWidget( ) const;
	virtual MusicToolWidget * getMusicToolWidget( ) const;
	virtual MusicFavoriteMenu * getMusicFavoriteMenu( ) const;
};

class MusicTitleWidgetTools {
public:
	virtual ~MusicTitleWidgetTools( ) = default;

private:
	friend class MusicCentreWidget;
	friend class MusicTitleWidget;
	static void updateMusicCentreWidgetTitleWidthInfo( MusicCentreWidget *music_centre_widget, MusicTitleWidget *music_title_widget );
	static void updateMusicTitleWidgetTitleWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );
};
#endif // MUSICCENTREWIDGET_H_H_HEAD__FILE__
