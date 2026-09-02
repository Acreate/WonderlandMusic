#include "musicInfoList.h"

#include "musicInfo.h"

#include <mutex/userMutex.h>
void MusicInfoList::loadFinished( MusicInfo *music_info ) {
	if( music_info == nullptr )
		return;
	bool isRelease = true;
	userMutex->lock( );
	for( index = 0; index < count; index += 1 )
		if( musicVectorDataPtr[ index ] == music_info ) {
			overLoadMusicVector.emplace_back( musicVectorDataPtr[ index ] );
			musicVectorDataPtr[ index ] = nullptr;
			if( count == overLoadMusicVector.size( ) ) {
				musicVector.clear( );
				musicVectorDataPtr = musicVector.data( );
				count = 0;
				break;
			}
			isRelease = false;
			break;
		}
	userMutex->unlock( );
	if( isRelease )
		delete music_info;
}

MusicInfoList::MusicInfoList( const std::vector< QString > &file_list ) : QThread( ) {
	count = file_list.size( );
	userMutex = new UserMutex;
	musicVector.resize( count );
	auto sourceDataPtr = file_list.data( );
	musicVectorDataPtr = musicVector.data( );
	MusicInfo *musicInfo;
	for( index = 0; index < count; index += 1 ) {
		musicInfo = new MusicInfo( sourceDataPtr[ index ] );
		musicVectorDataPtr[ index ] = musicInfo;
		connect( musicInfo, &MusicInfo::finished, [musicInfo, this]( ) {
			loadFinished( musicInfo );
		} );
	}
}
MusicInfoList::~MusicInfoList( ) {
	userMutex->lock( );
	auto musicInfo = overLoadMusicVector.data( );
	for( index = 0; index < count; index += 1 )
		delete musicInfo[ index ];
	overLoadMusicVector.clear( );
	count = 0;
	userMutex->unlock( );
	delete userMutex;
}
bool MusicInfoList::getOverLoadMusicVector( std::vector< MusicInfo * > &result_over_load_music_info_vector ) const {
	userMutex->lock( );
	if( 0 != count )
		return userMutex->result_unlock( false );
	result_over_load_music_info_vector = overLoadMusicVector;
	return userMutex->result_unlock( true );
}
void MusicInfoList::run( ) {
	userMutex->lock( );
	for( index = 0; index < count; index += 1 )
		if( musicVectorDataPtr[ index ]->isRead( ) )
			musicVectorDataPtr[ index ]->start( );
	userMutex->unlock( );
	while( count != 0 )
		currentThread( )->sleep( 500 );
}
