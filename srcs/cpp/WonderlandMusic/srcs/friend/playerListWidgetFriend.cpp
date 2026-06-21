#include "playerListWidgetFriend.h"

#include "../widget/playerListWidget.h"

PlayerListWidgetFriend::PlayerListWidgetFriend( QObject *parent, PlayerListWidget *player_list_widget ) : QObject( parent ), playerListWidget( player_list_widget ) {
}

bool PlayerListWidgetFriend::deleteDiskMusicFileList( const std::vector<MusicInfoItemWidget *> &file_path_info_vector ) {
	if( playerListWidget == nullptr )
		return false;

	return playerListWidget->deleteDiskMusicFileList( file_path_info_vector );
}

bool PlayerListWidgetFriend::removeListMusicFileList( const std::vector<MusicInfoItemWidget *> &file_path_info_vector ) {
	if( playerListWidget == nullptr )
		return false;
	return playerListWidget->removeListMusicFileList( file_path_info_vector );
}

bool PlayerListWidgetFriend::loadDiskMusicFileList( const std::vector< QString > &file_path_info_vector ) {
	if( playerListWidget == nullptr )
		return false;
	return playerListWidget->loadDiskMusicFileList( file_path_info_vector );
}

bool PlayerListWidgetFriend::loadDiskMusicDirList( const std::vector< QString > &file_path_info_vector ) {
	if( playerListWidget == nullptr )
		return false;
	return playerListWidget->loadDiskMusicDirList( file_path_info_vector );
}

bool PlayerListWidgetFriend::setCurrentPlayerMusicList( const std::vector< MusicInfoItemWidget * > &music_item_vector ) {
	if( playerListWidget == nullptr )
		return false;
	return playerListWidget->setCurrentPlayerMusicList( music_item_vector );
}

bool PlayerListWidgetFriend::setInsertPlayerMusicList( const std::vector< MusicInfoItemWidget * > &music_item_vector ) {
	if( playerListWidget == nullptr )
		return false;
	return playerListWidget->setInsertPlayerMusicList( music_item_vector );
}

bool PlayerListWidgetFriend::moveMusicToListTop( const std::vector< MusicInfoItemWidget * > &music_item_vector ) {
	if( playerListWidget == nullptr )
		return false;
	return playerListWidget->moveMusicToListTop( music_item_vector );
}

bool PlayerListWidgetFriend::moveMusicToListBottom( const std::vector< MusicInfoItemWidget * > &music_item_vector ) {
	if( playerListWidget == nullptr )
		return false;
	return playerListWidget->moveMusicToListBottom( music_item_vector );
}
