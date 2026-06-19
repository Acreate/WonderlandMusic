#ifndef PLAYLISTWIDGET_H_H_HEAD__FILE__
#define PLAYLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class PlayerWidgetMenu;
class PlayerListTopWidget;
class MusicInfoItem;
class QMutex;
class MusicInfoItemWidget;
class QMediaMetaData;

class PlayerListWidget : public QWidget {
	Q_OBJECT;

protected:
	QMutex *loadMusicFileMutex;

	QStringList loadMusicFileHistory;
	QVector< MusicInfoItemWidget * > musicInfoVector;
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
	QDateTime *beforeClickTime;
	MusicInfoItemWidget *activeLeftItemWidget;
	MusicInfoItemWidget *selectLeftItemWidget;
	QMutex *selectItemMutex;
	QVector< MusicInfoItemWidget * > selectItemWidgetVector;
	int drawPenWidth;
	QColor drawPenColor;
	QColor drawFillColor;
	QPen *pen;
	PlayerWidgetMenu* playerWidgetMenu;
protected:
	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int item_height, int split_width, int name_item_width, int singer_item_width, int duration_item_width, const QFont *item_font ) const;

	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target ) const;

	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int split_width ) const;

	virtual void doubleClickMusicItemWidget( MusicInfoItemWidget *double_target );

	virtual void apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target );

public:
	~PlayerListWidget( ) override;

	PlayerListWidget( QWidget *parent );

	// get+set
public:
	virtual void setItemWidth( const PlayerListTopWidget *player_list_top_widget );

	virtual void setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width );

	virtual int getSplitWidth( ) const;

	virtual void setSplitWidth( const int split_width );

	virtual int getMusicNameWidth( ) const;

	virtual void setMusicNameWidth( const int music_name_width );

	virtual int getMusicSingerWidth( ) const;

	virtual void setMusicSingerWidth( const int music_singer_width );

	virtual int getMusicDurationWidth( ) const;

	virtual void setMusicDurationWidth( const int format_string_duration_width );

	virtual MusicInfoItemWidget * getActiveLeftItemWidget( ) const;

	virtual MusicInfoItemWidget * getSelectLeftItemWidget( ) const;

	virtual QVector< MusicInfoItemWidget * > & getSelectItemWidgetVector( QVector< MusicInfoItemWidget * > &result_vector ) const;

	virtual QVector< MusicInfoItemWidget * > & getMusicInfoVector( QVector< MusicInfoItemWidget * > &result_vector ) const;

	virtual QVector< QString > & getListMusicFile( QVector< QString > &result_vector ) const;

	// 功能
public:
	virtual void updateItemWidget( );

	virtual void clearMusicInfoVector( );

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );

	virtual bool appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration );

	virtual bool fromFileLoadItemInfo( const QString &music_file_path );

	virtual bool renderMusicInfoItem( QImage &result_render_image, const MusicInfoItem *render_target ) const;

	// 重载
protected:
	void paintEvent( QPaintEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;

	void mouseMoveEvent( QMouseEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

Q_SIGNALS:
	void itemSelect( const QVector< MusicInfoItemWidget * > &select_vectir );

	void itemDoubleSelect( MusicInfoItemWidget *double_click_item_widget );
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
