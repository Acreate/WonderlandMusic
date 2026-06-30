#ifndef PLAYLISTWIDGET_H_H_HEAD__FILE__
#define PLAYLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>

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

class PlayerListWidget : public QWidget {
	Q_OBJECT;

public:
	enum class PlayerListWidgetState {
		None,
		Set_Player_Run,
		Set_Player_Next,
	};

protected:
	PlayerWindow *parentContent;
	PlayerListWidgetState widgetState = PlayerListWidgetState::None;
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
	UserMutex *playerMutex = nullptr;
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

	/// @brief 文件选择工作路径
	QString fileSelectWorkPath;
	/// @brief 目录选择工作路径
	QString dirSelectWorkPath;

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

	/// @brief 当播放时候，移动到列表，并且播放列表当中的首个音频时，调用该函数
	/// @param translation_vector_source 移动序列
	/// @return 失败返回 false
	virtual bool playerStatusTranslationMoveCurrentPlayer( const std::vector< MusicInfoItemWidget * > &translation_vector_source );

	/// @brief 当未播放时候，移动到列表，并且播放列表当中的首个音频时，调用该函数
	/// @param translation_vector_source 移动序列
	/// @return 失败返回 false
	virtual bool setoutStatusTranslationMoveCurrentPlayer( const std::vector< MusicInfoItemWidget * > &translation_vector_source );

	/// @brief 当播放时候，移动到列表后，并且播放列表当中的首个音频时，调用该函数
	/// @param translation_vector_source 移动序列
	/// @return 失败返回 false
	virtual bool playerStatusTranslationMoveCurrentPlayerNext( const std::vector< MusicInfoItemWidget * > &translation_vector_source );

	/// @brief 当未播放时候，移动到列表后，并且播放列表当中的首个音频时，调用该函数
	/// @param translation_vector_source 移动序列
	/// @return 失败返回 false
	virtual bool setoutStatusTranslationMoveCurrentPlayerNext( const std::vector< MusicInfoItemWidget * > &translation_vector_source );

protected Q_SLOTS:
	void playerStart_slot( const QString &player_music_file );

	void playerOver_slot( const QString &player_music_file );

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
	virtual bool deleteDiskMusicFileList( );

	/// @brief 从列表删除文件
	virtual bool removeListMusicFileList( );

	/// @brief 从磁盘路径加载文件
	virtual bool loadDiskMusicFileList( const std::vector< QString > &load_vector );

	/// @brief 从磁盘目录加载文件
	virtual bool loadDiskMusicDirList( const std::vector< QString > &load_vector );

	/// @brief 设置为当前播放列表
	virtual bool setCurrentPlayerMusicList( );

	/// @brief 插入当前播放列表后
	virtual bool setInsertPlayerMusicList( );

	/// @brief 移动列表到顶部
	virtual bool moveMusicToListTop( );

	/// @brief 移动列表到底部
	virtual bool moveMusicToListBottom( );

Q_SIGNALS:
	void itemSelect( );

	void itemDouble_Select( );

	void popMenu( );

	void playerMusic( );

	void playerNext( );
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
