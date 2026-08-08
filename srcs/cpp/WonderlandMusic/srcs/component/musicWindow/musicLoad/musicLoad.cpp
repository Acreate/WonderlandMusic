#include "musicLoad.h"

#include "../../../mutex/userMutex.h"

#include "../../../tools/pathTools.h"

#include "../Item/musicItem/musicItem.h"

#include "../musicCentreWidget/musicCentreWidget.h"
#include "../musicCentreWidget/musicListWidget/musicListWidget.h"
#include "../musicCentreWidget/musicfavoriteWidget/musicfavoriteWidget.h"

MusicLoad::MusicLoad( MusicCentreWidget *music_centre_widget ) : musicCentreWidget( music_centre_widget ) {
}
MusicLoad::~MusicLoad( ) {
	if( musicCentreWidget ) {
		auto musicFavoriteWidget = musicCentreWidget->getMusicFavoriteWidget( );
		if( musicFavoriteWidget )
			musicFavoriteWidget->removeMusicLoad( this );
	}
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
bool MusicLoad::unsafeHasMusicLoadMusicFileHistory( const QString &music_file ) const {
	size_t count = loadMusicItemsHistory.size( );
	if( count == 0 )
		return false;
	auto data = loadMusicItemsHistory.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ]->absoluteFilePath == music_file || data[ index ]->filePath == music_file )
			return true;
	return false;
}
bool MusicLoad::unsafeRemoveMusicItemsHistory( const MusicItem *music_item ) {
	size_t count = loadMusicItemsHistory.size( );
	if( count == 0 )
		return false;
	auto data = loadMusicItemsHistory.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == music_item ) {
			loadMusicItemsHistory.erase( index + loadMusicItemsHistory.begin( ) );
			return true;
		}
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
	auto currentFavoriteItem = getCurrentFavoriteItem( );
	if( currentFavoriteItem == nullptr )
		return false;
	QFileInfo info( music_file_path );
	if( info.exists( ) == false )
		return false;
	auto absoluteFilePath = info.absoluteFilePath( );
	if( PathTools::isMusicFile( absoluteFilePath ) == false )
		return false;
	userMutex->lock( );
	auto musicItem = new MusicItem( currentFavoriteItem, music_file_path );
	musicItem->loadPtr = this;
	loadMusicItemsHistory.emplace_back( musicItem );
	userMutex->unlock( );
	return true;
}
bool MusicLoad::loadMusicDir( const QString &music_dir_path ) {
	bool result = false;

	auto currentFavoriteItem = getCurrentFavoriteItem( );
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
	userMutex->lock( );
	auto result = unsafeRemoveMusicItemsHistory( music_item );
	userMutex->unlock( );
	return result;
}
bool MusicLoad::hasMusicLoadMusicFileHistory( const QString &music_file ) {
	userMutex->lock( );
	auto result = unsafeHasMusicLoadMusicFileHistory( music_file );
	userMutex->unlock( );
	return result;
}
FavoriteItem * MusicLoad::getCurrentFavoriteItem( ) const {
	if( musicCentreWidget == nullptr )
		return nullptr;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return nullptr;
	auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
	return currentFavoriteItem;
}

bool MusicLoadTools::createMusicLoad( MusicLoad **music_load, MusicCentreWidget *music_centre_widget ) {
	if( music_centre_widget == nullptr )
		return false;
	*music_load = new MusicLoad( music_centre_widget );
	return *music_load;
}
bool MusicLoadTools::releaseMusicLoad( MusicLoad **music_load ) {
	if( *music_load == nullptr )
		return false;
	delete *music_load;
	*music_load = nullptr;
	return true;
}
bool MusicLoadTools::setMusicListWidget( MusicLoad *music_load, MusicCentreWidget *music_centre_widget ) {
	if( music_load == nullptr )
		return false;
	music_load->musicCentreWidget = music_centre_widget;
	return true;
}
