#include "musicFavoriteItem.h"

#include <qimage.h>

#include "../application/appInstance/appDataManage.h"

#include "../component/musicWindow/musicCentreWidget/musicCentreWidget.h"

#include "../mutex/userMutex.h"

bool MusicFavoriteItem::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicFavoriteItemUserMutex->lock( );
	musicCentreWidget = music_centre_widget;
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
bool MusicFavoriteItem::getName( QString &result_name ) const {
	musicFavoriteItemUserMutex->lock( );
	result_name = name;
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
bool MusicFavoriteItem::addMusicItem( IMusicItem *music_item ) {
	musicFavoriteItemUserMutex->lock( );
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
bool MusicFavoriteItem::removeMusicItem( IMusicItem *music_item ) {
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
bool MusicFavoriteItem::clear( ) {
	musicFavoriteItemUserMutex->lock( );
	musicItemVector.clear( );
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
bool MusicFavoriteItem::update( ) {
	if( musicCentreWidget == nullptr )
		return false;
	musicCentreWidget->update( );
	return true;
}
bool MusicFavoriteItem::fromIndexGetMusicItem( IMusicItem *&result_music_item_vector, const size_t &result_count ) {
	return musicFavoriteItemUserMutex->auto_job< bool >( []( ) ->bool {
		return true;
	} );
}
bool MusicFavoriteItem::fromMusicItemGetIndex( size_t &result_index, const IMusicItem *music_item ) {
	return musicFavoriteItemUserMutex->auto_job< bool >( []( ) {
		return true;
	} );
}
bool MusicFavoriteItem::fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) {
	return musicFavoriteItemUserMutex->auto_job< bool >( []( ) {
		return true;
	} );
}
bool MusicFavoriteItem::fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) {
	return musicFavoriteItemUserMutex->auto_job< bool >( []( ) {
		return true;
	} );
}
bool MusicFavoriteItem::fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) {
	return musicFavoriteItemUserMutex->auto_job< bool >( []( ) {
		return true;
	} );
}
bool MusicFavoriteItem::fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) {
	return musicFavoriteItemUserMutex->auto_job< bool >( []( ) {
		return true;
	} );
}
size_t MusicFavoriteItem::getMusicVectorClone( std::vector< IMusicItem * > &result_clone_vector ) const {
	return musicFavoriteItemUserMutex->auto_job< size_t >( [this, &result_clone_vector]( ) {
		size_t resultCount = musicItemVector.size( );
		result_clone_vector.resize( resultCount );
		if( resultCount == 0 )
			return resultCount;
		auto source = musicItemVector.data( );
		auto dest = result_clone_vector.data( );
		size_t index = 0;
		for( ; index < resultCount; index += 1 )
			dest[ index ] = source[ index ];
		return resultCount;
	} );
}
void MusicFavoriteItem::setName( const QString &name ) {
	this->name = name;
}
MusicFavoriteItem::MusicFavoriteItem( ) {
	appendTypeInfo( this );
	musicFavoriteItemUserMutex = new UserMutex;
}
MusicFavoriteItem::~MusicFavoriteItem( ) {
	musicFavoriteItemUserMutex->lock( );
	musicItemVector.clear( );
	musicFavoriteItemUserMutex->unlock( );
	delete musicFavoriteItemUserMutex;
	musicFavoriteItemUserMutex = nullptr;
}
