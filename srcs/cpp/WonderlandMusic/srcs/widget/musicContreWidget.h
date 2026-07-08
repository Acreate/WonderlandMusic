#ifndef MUSICCONTREWIDGET_H_H_HEAD__FILE__
#define MUSICCONTREWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"
class MusicItem;
class PlayerListTopWidget;
class UserMutex;
class MusicInfoItemWidget;

class MusicContreWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;
	friend class MusicContreScrollArea;

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
	virtual void setMusicInfoVector( const std::vector< MusicItem * > &load_music_items );
	virtual void setItemPlayerListTopWidgetWidth( const PlayerListTopWidget *player_list_top_widget );
	virtual void setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width );
	virtual void updateItemWidget( );
	virtual void removeRepetition( );
	virtual const std::vector< MusicInfoItemWidget * > & getMusicInfoVector( ) const;
	virtual void setMusicInfoVector( const std::vector< MusicInfoItemWidget * > &music_info_vector );
	virtual void clearMusicItem( );

	virtual void clearMusicInfoItemWidget( ) {
		clearMusicItem( );
	}

protected:
	virtual void apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target, bool check_key_board_modifier );
	virtual bool selectKeyShiftModifier( );
	virtual bool selectKeyControlModifier( );

protected:
	bool deleteResource( ) override;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
	virtual MusicInfoItemWidget * highlghtItem( const QPoint &pos );
	virtual MusicInfoItemWidget * selectorItem( const QPoint &pos );
	virtual MusicInfoItemWidget * showItemMenu( const QPoint &pos );
	// 重载
protected:
	void paintEvent( QPaintEvent *event ) override;
	void resizeEvent( QResizeEvent *event ) override;
Q_SIGNALS:
	void signal_item_select( );
	void signal_item_double_select( );
	void signal_pop_menu( );
};
#endif // MUSICCONTREWIDGET_H_H_HEAD__FILE__
