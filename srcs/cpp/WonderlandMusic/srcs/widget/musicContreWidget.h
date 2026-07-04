#ifndef MUSICCONTREWIDGET_H_H_HEAD__FILE__
#define MUSICCONTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class MusicItem;
class PlayerListTopWidget;
class UserMutex;
class MusicInfoItemWidget;
class PlayerListWidgetMenu;
class PlayerWindow;

class MusicContreWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	int currentWidgetWidth;
	int currentWidgetHeight;
	int widgetBeforeWidth;
	int widgetAfterWidth;
	int splitWidth;
	int indexWidth;
	int musicNameWidth;
	int musicSingerWidth;
	int musicDurationWidth;
	qint64 doubleClickIntervalTimeMilliSecond;
	UserMutex *musicInfoMutex = nullptr;
	QDateTime *beforeClickTime = nullptr;
	std::vector< MusicInfoItemWidget * > musicInfoVector;
	MusicInfoItemWidget *activeLeftItemWidget = nullptr;
	MusicInfoItemWidget *selectLeftItemWidget = nullptr;
	std::vector< MusicInfoItemWidget * > selectItemWidgetVector;
	int drawPenWidth;
	QColor drawPenColor;
	QColor drawFillColor;
	QPen *pen = nullptr;

public:
	MusicContreWidget( QWidget *parent );

	virtual bool showFavorteMusicContreList( const QString &music_favorte_widget );

	virtual void setItemVector( const std::vector< MusicItem * > &load_music_items );

	virtual void setItemWidth( const PlayerListTopWidget *player_list_top_widget );

	virtual void setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width );

	virtual void updateItemWidget( );

	virtual void removeRepetition( );

protected:
	virtual void apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target, bool check_key_board_modifier );

	virtual bool selectKeyShiftModifier( );

	virtual bool selectKeyControlModifier( );

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	// 重载
protected:
	void paintEvent( QPaintEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;

	void mouseMoveEvent( QMouseEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

Q_SIGNALS:
	void signal_item_select( );

	void signal_item_double_select( );
};

#endif // MUSICCONTREWIDGET_H_H_HEAD__FILE__
