#ifndef PLAYLISTWIDGET_H_H_HEAD__FILE__
#define PLAYLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class MusicPlayer;

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
	friend class PlayerListWidgetFriend;

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
	MusicInfoItemWidget *playerItemWidget = nullptr;
	std::vector< MusicInfoItemWidget * > *selectItemWidgetVector = nullptr;
	int drawPenWidth;
	QColor drawPenColor;
	QColor drawFillColor;
	QPen *pen = nullptr;
	MusicPlayer *musicPlayer;

protected:
	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int item_height, int split_width, int name_item_width, int singer_item_width, int duration_item_width, const QFont *item_font ) const;

	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target ) const;

	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int split_width ) const;

	/// @brief 双击时，调用该函数
	/// @param double_target 被双击的目标选项
	virtual void doubleClickMusicItemWidget( MusicInfoItemWidget *double_target );

	virtual void apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target, bool check_key_board_modifier );

	virtual bool selectKeyShiftModifier( );

	virtual bool selectKeyControlModifier( );

	virtual void releaseResource( );

	virtual bool removeMusicInfoVector( const std::vector< MusicInfoItemWidget * > &remove_source_target, std::vector< MusicInfoItemWidget * > &result_move_target );

	virtual void removeRepetition( );

	virtual bool fromFilePathFindItemWidget( size_t &index, std::vector< MusicInfoItemWidget * > &find_vector_source, const QString &find_file_path_target ) const;

protected Q_SLOTS:
	void playerStart_slot( const QString &player_music_file );

	void playerOver_slot( const QString &player_music_file );

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

protected:
	/// @brief 从磁盘删除文件
	/// @param file_path_info_vector 删除路径列表
	virtual bool deleteDiskMusicFileList( const std::vector< MusicInfoItemWidget * > &file_path_info_vector );

	/// @brief 从列表删除文件
	/// @param file_path_info_vector 删除路径列表
	virtual bool removeListMusicFileList( const std::vector< MusicInfoItemWidget * > &file_path_info_vector );

	/// @brief 从磁盘路径加载文件
	/// @param file_path_info_vector 加载文件列表
	virtual bool loadDiskMusicFileList( const std::vector< QString > &file_path_info_vector );

	/// @brief 从磁盘目录加载文件
	/// @param file_path_info_vector 磁盘目录列表
	virtual bool loadDiskMusicDirList( const std::vector< QString > &file_path_info_vector );

	/// @brief 设置为当前播放列表
	/// @param music_item_vector 播放的列表
	virtual bool setCurrentPlayerMusicList( const std::vector< MusicInfoItemWidget * > &music_item_vector );

	/// @brief 插入当前播放列表后
	/// @param music_item_vector 插入的列表
	virtual bool setInsertPlayerMusicList( const std::vector< MusicInfoItemWidget * > &music_item_vector );

	/// @brief 移动列表到顶部
	/// @param music_item_vector 被移动的列表
	virtual bool moveMusicToListTop( const std::vector< MusicInfoItemWidget * > &music_item_vector );

	/// @brief 移动列表到底部
	/// @param music_item_vector 被移动的列表
	virtual bool moveMusicToListBottom( const std::vector< MusicInfoItemWidget * > &music_item_vector );

Q_SIGNALS:
	void itemSelect( const std::vector< MusicInfoItemWidget * > &select_vectir );

	void itemDoubleSelect( MusicInfoItemWidget *double_click_item_widget );

	void popMenu( );
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
