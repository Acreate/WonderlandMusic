#ifndef PLAYLISTWIDGET_H_H_HEAD__FILE__
#define PLAYLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../application/appCore.h"

class PlayerWindow;
class UserMutex;
class MusicPlayer;

namespace std {
	class mutex;
}

class PlayerWidgetMenu;
class PlayerListTopWidget;
class MusicInfoItem;
class MusicInfoItemWidget;
class QMediaMetaData;

class PlayerListWidget : public QWidget, public AppCore {
	Q_OBJECT;

public:
	enum class PlayerListWidgetState {
		None,
		Set_Player_Run,
		Set_Player_Next,
	};

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
	UserMutex *musicInfoMutex = nullptr;
	std::vector< MusicInfoItemWidget * > *musicInfoVector = nullptr;
	QDateTime *beforeClickTime = nullptr;
	MusicInfoItemWidget *activeLeftItemWidget = nullptr;
	MusicInfoItemWidget *selectLeftItemWidget = nullptr;
	std::vector< MusicInfoItemWidget * > *selectItemWidgetVector = nullptr;
	int drawPenWidth;
	QColor drawPenColor;
	QColor drawFillColor;
	QPen *pen = nullptr;

protected:
	virtual void apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target, bool check_key_board_modifier );

	virtual bool selectKeyShiftModifier( );

	virtual bool selectKeyControlModifier( );

	bool deleteResource( ) override;

	virtual void removeRepetition( );

public:
	~PlayerListWidget( ) override;

	PlayerListWidget( QWidget *parent = nullptr );

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

	virtual void setWidgetMusicInfoVector( std::vector< MusicInfoItemWidget * > &new_vector ) const;

	virtual std::vector< MusicInfoItemWidget * > & getWidgetMusicInfoVector( std::vector< MusicInfoItemWidget * > &result_vector ) const;

	virtual std::vector< QString > & getListMusicFile( std::vector< QString > &result_vector ) const;

	// 功能
public:
	virtual qint64 getMusicDuratction( ) const;

	virtual void updateItemWidget( );

	virtual void clearMusicInfoVector( );

	bool init( ) override;

	virtual void clear( );

	// 重载
protected:
	void paintEvent( QPaintEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;

	void mouseMoveEvent( QMouseEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

Q_SIGNALS:
	void itemSelect( );

	void itemDouble_Select( );

	void popMenu( );

	void playerMusic( );

	void playerNext( );
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
