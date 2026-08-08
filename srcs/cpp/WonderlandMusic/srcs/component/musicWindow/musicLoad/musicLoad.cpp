#include "musicLoad.h"

#include "../../../mutex/userMutex.h"

#include "../../../tools/pathTools.h"

#include "../Item/musicItem/musicItem.h"

#include "../musicCentreWidget/musicListWidget/musicListWidget.h"

MusicLoad::MusicLoad( MusicListWidget *music_list_widget ) : musicListWidget( music_list_widget ) {
}
MusicLoad::~MusicLoad( ) {
	if( musicListWidget )
		musicListWidget->removeMusicLoad( this );
	deleteResource( );
}
bool MusicLoad::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	unsafeDeleteMusicItemsHistory( );
	userMutex->unlock( );
	return true;
}
void MusicLoad::unsafeDeleteMusicItemsHistory( ) {
	size_t count = loadMusicItemsHistory.size( );
	if( count == 0 )
		return;
	auto data = loadMusicItemsHistory.data( );
	size_t index = 0;
	for( ; index < count; index += 1 ) {
		data[ index ]->loadPtr = nullptr;
		delete data[ index ];
	}
	loadMusicItemsHistory.clear( );
}
bool MusicLoad::unsafeHasMusicLoadMusicFileHistory( const QString &music_file ) {
	return false;
}
bool MusicLoad::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	return true;
}
bool MusicLoad::init( ) {
	return true;
}
bool MusicLoad::initAfter( ) {
	return true;
}
bool MusicLoad::loadMusicFile( const QString &music_file_path ) {
	auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
	if( currentFavoriteItem == nullptr )
		return false;
	QFileInfo info( music_file_path );
	if( info.exists( ) == false )
		return false;
	auto absoluteFilePath = info.absoluteFilePath( );
	if( PathTools::isMusicFile( absoluteFilePath ) == false )
		return false;
	auto musicItem = new MusicItem( currentFavoriteItem, music_file_path );
	musicItem->loadPtr = this;
	loadMusicItemsHistory.emplace_back( musicItem );
	return true;
}
bool MusicLoad::loadMusicDir( const QString &music_dir_path ) {
	bool result = false;

	auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
	if( currentFavoriteItem ) {
		QStringList filterMusicFileList;
		QStringList getFileList;
		qsizetype musicFileCount;
		if( PathTools::entryFilePath( filterMusicFileList, music_dir_path ) ) {
			musicFileCount = PathTools::filterFile( getFileList, filterMusicFileList );
			if( musicFileCount ) {
				musicFileCount = PathTools::filterMusicFile( filterMusicFileList, getFileList );
				if( musicFileCount ) {
					auto data = filterMusicFileList.data( );
					qsizetype index;
					userMutex->lock( );
					for( index = 0; index < musicFileCount; index += 1 ) {
						auto musicItem = new MusicItem( currentFavoriteItem, data[ index ] );
						musicItem->loadPtr = this;
						loadMusicItemsHistory.emplace_back( musicItem );
					}
					userMutex->unlock( );
					result = true;
				}
			}
		}
	}
	return result;
}
bool MusicLoad::removeMusicItemsHistory( const MusicItem *music_item ) {
	return false;
}
bool MusicLoad::hasMusicLoadMusicFileHistory( const QString &music_file ) {
	userMutex->lock( );
	auto result = unsafeHasMusicLoadMusicFileHistory( music_file );
	userMutex->unlock( );
	return result;
}
bool MusicLoadTools::createMusicLoad( MusicLoad **music_load, MusicListWidget *music_list_widget ) {
	if( music_list_widget == nullptr )
		return false;
	*music_load = new MusicLoad( music_list_widget );
	return true;
}
bool MusicLoadTools::releaseMusicLoad( MusicLoad **music_load ) {
	if( music_load == nullptr || *music_load == nullptr )
		return false;
	delete *music_load;
	*music_load = nullptr;
	return true;
}
bool MusicLoadTools::setMusicListWidget( MusicLoad *music_load, MusicListWidget *music_list_widget ) {
	if( music_load == nullptr )
		return false;
	music_load->musicListWidget = music_list_widget;
	return true;
}
