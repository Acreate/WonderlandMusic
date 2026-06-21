#ifndef PLAYERLISTWIDGETFRIEND_H_H_HEAD__FILE__
#define PLAYERLISTWIDGETFRIEND_H_H_HEAD__FILE__
#include <QObject>

class PlayerListWidget;
class MusicInfoItemWidget;

class PlayerListWidgetFriend : public QObject {
	friend class PlayerWidgetMenu;

protected:
	PlayerListWidget *playerListWidget;

	PlayerListWidgetFriend( QObject *parent, PlayerListWidget *player_list_widget );

protected:
	/// @brief 从磁盘删除文件
	/// @param file_path_info_vector 删除路径列表
	virtual bool deleteDiskMusicFileList( const std::vector< QString > &file_path_info_vector );

	/// @brief 从列表删除文件
	/// @param file_path_info_vector 删除路径列表
	virtual bool removeListMusicFileList( const std::vector< QString > &file_path_info_vector );

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
};

#endif // PLAYERLISTWIDGETFRIEND_H_H_HEAD__FILE__
