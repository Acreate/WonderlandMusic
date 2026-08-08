#include "musicLoad.h"

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
	return true;
}
bool MusicLoad::initBefore( ) {
	return true;
}
bool MusicLoad::init( ) {
	return true;
}
bool MusicLoad::initAfter( ) {
	return true;
}
bool MusicLoad::loadMusicFile( const QString &music_file_path ) {
	QStringList filterMusicFileList;
	QStringList getFileList;
	qsizetype musicFileCount;
	if( PathTools::entryFilePath( filterMusicFileList, music_file_path ) == false )
		return false;
	musicFileCount = PathTools::filterFile( getFileList, filterMusicFileList );
	if( musicFileCount == 0 )
		return false;
	musicFileCount = PathTools::filterMusicFile( filterMusicFileList, getFileList );
	if( musicFileCount == 0 )
		return false;
	auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
	auto data = filterMusicFileList.data( );
	qsizetype index;
	for( index = 0; index < musicFileCount; index += 1 )
		MusicItem( currentFavoriteItem, data[ index ] );
	return true;
}
bool MusicLoad::loadMusicDir( const QString &music_dir_path ) {
	return true;
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
