#ifndef PLAYERWIDGETMENU_H_H_HEAD__FILE__
#define PLAYERWIDGETMENU_H_H_HEAD__FILE__

#include <QMenu>
class PlayerListWidgetFriend;
class JsonFileKey;
class PlayerListMenuJsonKey;
class PlayerListMenuTranslate;
class MusicDecoder;
class AppTranslate;
class AppInstance;
class MusicInfoItemWidget;
class PlayerListWidget;

class PlayerWidgetMenu : public QMenu {
	Q_OBJECT;

protected:
	AppInstance *appInstance;
	const AppTranslate *appTranslate;
	PlayerListMenuTranslate *playerListMenuTranslate;
	MusicDecoder *musicDecoder;
	const JsonFileKey *jsonFileKey;
	PlayerListMenuJsonKey *playerListMenuJsonKey;
	/// @brief 文件选择工作路径
	QString fileSelectWorkPath;
	/// @brief 目录选择工作路径
	QString dirSelectWorkPath;
	PlayerListWidget *playerListWidget;
	QVector< MusicInfoItemWidget * > musicInfoItemWidgetVector;
	/// @brief 播放菜单
	QMenu *playerMenu;
	/// @brief 删除菜单
	QMenu *removeMenu;
	/// @brief 控制菜单
	QMenu *controlMenu;
	/// @brief 插入当前播放列表
	QAction *insterPlay;
	/// @brief 播放当前列表
	QAction *setplay;
	/// @brief 移动到顶部
	QAction *moveTop;
	/// @brief 移动到底部
	QAction *moveBottom;
	/// @brief 移除选中
	QAction *removeMusic;
	/// @brief 删除选中
	QAction *deleteMusic;
	/// @brief 加载菜单
	QMenu *loadMenu;
	/// @brief 添加选择文件到集
	QAction *addMultiFileMusicToCollectionAction;
	/// @brief 添加选择目录到集
	QAction *addMultiMusicDirToCollection;
	PlayerListWidgetFriend *playerListWidgetFriend = nullptr;

protected:
	virtual void deleteResource( );

public:
	PlayerWidgetMenu( PlayerListWidget *player_list_widget );

	virtual bool init( );

	virtual bool loadJsonPathInfo( );

	virtual bool writeJsonPathInfo( );

protected:
	virtual bool initVar( );

	virtual bool initSubMenu( );

	virtual bool initSubMenuAcction( );

	virtual bool initConnectAcction( );

	virtual void loadDiskFile( );

	virtual void loadDiskDir( );

	virtual void setCurrentSelectPlay( );

	virtual void insterCurrentSelectPlay( );

	virtual void removePlayListSelectInfo( );

	virtual void deletePlayListSelectFile( );

	virtual void selectListMoveTop( );

	virtual void selectListMoveBottom( );

protected:
	void hideEvent( QHideEvent * ) override;

	/// @brief 从磁盘删除文件
	/// @param file_path_info_vector 删除路径列表
	virtual void deleteDiskMusicFileList( const std::vector< MusicInfoItemWidget * > &file_path_info_vector );

	/// @brief 从列表删除文件
	/// @param file_path_info_vector 删除路径列表
	virtual void removeListMusicFileList( const std::vector< MusicInfoItemWidget * > &file_path_info_vector );

	/// @brief 从磁盘路径加载文件
	/// @param file_path_info_vector 加载文件列表
	virtual void loadDiskMusicFileList( const std::vector< QString > &file_path_info_vector );

	/// @brief 从磁盘目录加载文件
	/// @param file_path_info_vector 磁盘目录列表
	virtual void loadDiskMusicDirList( const std::vector< QString > &file_path_info_vector );

	/// @brief 设置为当前播放列表
	/// @param music_item_vector 播放的列表
	virtual void setCurrentPlayerMusicList( const std::vector< MusicInfoItemWidget * > &music_item_vector );

	/// @brief 插入当前播放列表后
	/// @param music_item_vector 插入的列表
	virtual void setInsertPlayerMusicList( const std::vector< MusicInfoItemWidget * > &music_item_vector );

	/// @brief 移动列表到顶部
	/// @param music_item_vector 被移动的列表
	virtual void moveMusicToListTop( const std::vector< MusicInfoItemWidget * > &music_item_vector );

	/// @brief 移动列表到底部
	/// @param music_item_vector 被移动的列表
	virtual void moveMusicToListBottom( const std::vector< MusicInfoItemWidget * > &music_item_vector );
};

#endif // PLAYERWIDGETMENU_H_H_HEAD__FILE__
