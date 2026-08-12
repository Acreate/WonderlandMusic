#include "musicLoad.h"

#include "../../../mutex/userMutex.h"

#include "../../../tools/pathTools.h"

#include "../Item/favoriteItem/favoriteItem.h"
#include "../Item/musicItem/musicItem.h"

MusicLoad::MusicLoad( FavoriteItem *favorite_item ) : favoriteItem( favorite_item ) {
}
MusicLoad::~MusicLoad( ) {
	if( favoriteItem )
		favoriteItem->removeMusicLoad( this );
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
size_t MusicLoad::loadMusicFile( const std::vector< QString > &music_file_path_vector ) {
	size_t result = 0;
	size_t count = music_file_path_vector.size( );
	if( count == 0 )
		return result;
	size_t index = 0;
	auto data = music_file_path_vector.data( );
	for( ; index < count; index += 1 )
		result += loadMusicFile( data[ index ] );
	return result;
}
size_t MusicLoad::loadMusicFile( const std::list< QString > &music_file_path_list ) {
	size_t result = 0;
	auto iterator = music_file_path_list.begin( );
	auto end = music_file_path_list.end( );
	if( iterator == end )
		return result;
	for( ; iterator != end; ++iterator )
		result += loadMusicFile( *iterator );
	return result;
}
size_t MusicLoad::loadMusicFile( const QStringList &music_file_path_list ) {
	size_t result = 0;
	size_t count = music_file_path_list.size( );
	if( count == 0 )
		return result;
	size_t index = 0;
	auto data = music_file_path_list.data( );
	for( ; index < count; index += 1 )
		result += loadMusicFile( data[ index ] );
	return result;
}
size_t MusicLoad::loadMusicFile( const QString &music_file_path ) {
	if( favoriteItem == nullptr )
		return 0;
	QFileInfo info( music_file_path );
	if( info.exists( ) == false )
		return 0;
	auto absoluteFilePath = info.absoluteFilePath( );
	if( PathTools::isMusicFile( absoluteFilePath ) == false )
		return 0;
	userMutex->lock( );
	auto musicItem = new MusicItem( favoriteItem, music_file_path );
	musicItem->loadPtr = this;
	loadMusicItemsHistory.emplace_back( musicItem );
	userMutex->unlock( );
	return 1;
}
bool MusicLoad::loadMusicDir( const QString &music_dir_path ) {
	bool result = false;

	if( favoriteItem ) {
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
						auto musicItem = new MusicItem( favoriteItem, data[ index ] );
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
FavoriteItem * MusicLoad::getFavoriteItem( ) const {
	return favoriteItem;
}
bool MusicLoad::update( ) {
	return favoriteItem->update( );
}
