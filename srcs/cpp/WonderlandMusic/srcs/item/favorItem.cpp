#include "favorItem.h"

#include "musicItem.h"

FavorItem::FavorItem( const QString &name, const std::vector< MusicItem * > &music_itemv_vector ) : name( name ),
	musicItemvVector( music_itemv_vector ) {
}

FavorItem::FavorItem( const QString &name ) : name( name ) {
}

FavorItem::~FavorItem( ) {
}

const QString & FavorItem::getName( ) const {
	return name;
}

const std::vector< MusicItem * > & FavorItem::getMusicItemvVector( ) const {
	return musicItemvVector;
}

bool FavorItem::appendMusicItem( MusicItem *music_item ) {
	size_t count = musicItemvVector.size( );
	if( count == 0 ) {
		musicItemvVector.emplace_back( music_item );
		return true;
	}
	auto data = musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ] == music_item || data[ index ]->isMusicFile( *music_item ) )
			return false;
	musicItemvVector.emplace_back( music_item );
	return true;
}

std::vector< MusicItem * > FavorItem::findMusicName( const QString &find_name ) const {
	std::vector< MusicItem * > result;
	size_t count = musicItemvVector.size( );
	if( count == 0 )
		return result;
	auto data = musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->getMusicName( ) == find_name )
			result.emplace_back( data[ index ] );
	return result;
}

std::vector< MusicItem * > FavorItem::findMusicFilePath( const QString &find_file_path ) const {
	std::vector< MusicItem * > result;
	size_t count = musicItemvVector.size( );
	if( count == 0 )
		return result;
	auto data = musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->isMusicFile( find_file_path ) )
			result.emplace_back( data[ index ] );
	return result;
}

std::vector< MusicItem * > FavorItem::findMusicMusicSinger( const QString &music_singer ) const {
	std::vector< MusicItem * > result;
	size_t count = musicItemvVector.size( );
	if( count == 0 )
		return result;
	auto data = musicItemvVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->getMusicSinger( ) == music_singer )
			result.emplace_back( data[ index ] );
	return result;
}
