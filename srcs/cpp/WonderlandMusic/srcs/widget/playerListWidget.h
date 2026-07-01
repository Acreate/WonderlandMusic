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
	PlayerWindow *parentContent;
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

	virtual bool removeMusicInfoVector( const std::vector< MusicInfoItemWidget * > &remove_source_target, std::vector< MusicInfoItemWidget * > &result_move_target );

	virtual void removeRepetition( );

public:
	~PlayerListWidget( ) override;

	PlayerListWidget( PlayerWindow *parent );

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
	virtual qint64 getMusicDuratction( ) const;

	virtual void updateItemWidget( );

	virtual void clearMusicInfoVector( );

	virtual bool appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration );

	virtual bool fromFileLoadItemInfo( const QString &music_file_path );

	bool init( ) override;

	/// @brief 从磁盘路径加载文件
	virtual bool loadDiskMusicFileList( const std::vector< QString > &load_vector );

	/// @brief 从磁盘目录加载文件
	virtual bool loadDiskMusicDirList( const std::vector< QString > &load_vector );

	// 重载
protected:
	void paintEvent( QPaintEvent *event ) override;

	void resizeEvent( QResizeEvent *event ) override;

	void mouseMoveEvent( QMouseEvent *event ) override;

	void mouseReleaseEvent( QMouseEvent *event ) override;

protected:
	/// @brief 从磁盘删除文件
	virtual bool deleteDiskMusicFileList( );

	/// @brief 从列表删除文件
	virtual bool removeListMusicFileList( );

Q_SIGNALS:
	void itemSelect( );

	void itemDouble_Select( );

	void popMenu( );

	void playerMusic( );

	void playerNext( );
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
