#ifndef PLAYLISTWIDGET_H_H_HEAD__FILE__
#define PLAYLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

namespace std {
	class mutex;
}

class PlayerWidgetMenu;
class PlayerListTopWidget;
class MusicInfoItem;
class MusicInfoItemWidget;
class QMediaMetaData;

class PlayerListWidget : public QWidget {
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
	QStringList loadMusicFileHistory;
	std::mutex *updateMuex = nullptr;
	std::mutex *musicInfoMutex = nullptr;
	std::vector< MusicInfoItemWidget * > *musicInfoVector = nullptr;
	QDateTime *beforeClickTime = nullptr;
	MusicInfoItemWidget *activeLeftItemWidget = nullptr;
	MusicInfoItemWidget *selectLeftItemWidget = nullptr;
	std::mutex *selectItemWidgetMutex = nullptr;
	std::vector< MusicInfoItemWidget * > *selectItemWidgetVector = nullptr;
	int drawPenWidth;
	QColor drawPenColor;
	QColor drawFillColor;
	QPen *pen = nullptr;

protected:
	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int item_height, int split_width, int name_item_width, int singer_item_width, int duration_item_width, const QFont *item_font ) const;

	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target ) const;

	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int split_width ) const;

	virtual void doubleClickMusicItemWidget( MusicInfoItemWidget *double_target );

	virtual void apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target );

	virtual bool selectKeyShiftModifier( );

	virtual bool selectKeyControlModifier( );

	virtual bool selectKeyDefaultModifier( );

	virtual void releaseResource( );

public:
	~PlayerListWidget( ) override;

	PlayerListWidget( QWidget *parent );

	// get+set
public:
	virtual void setItemWidth( const PlayerListTopWidget *player_list_top_widget );

	virtual void setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width );

	virtual int getSplitWidth( ) const;

	virtual int getMusicNameWidth( ) const;

	virtual int getMusicSingerWidth( ) const;

	virtual int getMusicDurationWidth( ) const;

	virtual MusicInfoItemWidget * getActiveLeftItemWidget( ) const;

	virtual MusicInfoItemWidget * getSelectLeftItemWidget( ) const;

	virtual std::vector< MusicInfoItemWidget * > & getSelectItemWidgetVector( std::vector< MusicInfoItemWidget * > &result_vector ) const;

	virtual std::vector< MusicInfoItemWidget * > & getMusicInfoVector( std::vector< MusicInfoItemWidget * > &result_vector ) const;

	virtual std::vector< QString > & getListMusicFile( std::vector< QString > &result_vector ) const;

	// 功能
public:
	virtual void updateItemWidget( );

	virtual void clearMusicInfoVector( );

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );

	virtual bool appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration );

	virtual bool fromFileLoadItemInfo( const QString &music_file_path );

	virtual bool renderMusicInfoItem( QImage &result_render_image, const MusicInfoItem *render_target ) const;

	virtual bool init( );

	// 重载
protected:
	void paintEvent( QPaintEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;

	void mouseMoveEvent( QMouseEvent *event ) override;

	void hideEvent( QHideEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

Q_SIGNALS:
	void itemSelect( const std::vector< MusicInfoItemWidget * > &select_vectir );

	void itemDoubleSelect( MusicInfoItemWidget *double_click_item_widget );
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
