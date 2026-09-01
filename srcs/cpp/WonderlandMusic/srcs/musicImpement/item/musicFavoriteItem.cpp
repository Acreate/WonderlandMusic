#include "musicFavoriteItem.h"

#include <qimage.h>

#include <application/appInstance/appDataManage.h>

#include <component/musicWindow/interface/item/iMusicItem.h>

#include <mutex/userMutex.h>

#include "../../component/musicWindow/interface/widget/iMusicCentreWidget.h"

#include "../itemWidget/musicFavoriteItemWidget.h"

bool MusicFavoriteItem::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
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
	musicCentreWidget->repaintMusicCentreWidget( );
	return true;
}
bool MusicFavoriteItem::fromIndexGetMusicItem( IMusicItem *&result_music_item_vector, const size_t &result_count ) {
	bool result = true;
	musicFavoriteItemUserMutex->auto_job( [&result]( ) {
	} );
	return result;
}
bool MusicFavoriteItem::fromMusicItemGetIndex( size_t &result_index, const IMusicItem *music_item ) {
	bool result = true;
	musicFavoriteItemUserMutex->auto_job( [&result]( ) {
	} );
	return result;
}
bool MusicFavoriteItem::fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) {
	bool result = true;
	musicFavoriteItemUserMutex->auto_job( [&result]( ) {
	} );
	return result;
}
bool MusicFavoriteItem::fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) {
	bool result = true;
	musicFavoriteItemUserMutex->auto_job( [&result]( ) {
	} );
	return result;
}
bool MusicFavoriteItem::fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) {
	bool result = true;
	musicFavoriteItemUserMutex->auto_job( [&result]( ) {
	} );
	return result;
}
bool MusicFavoriteItem::fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) {
	bool result = true;
	musicFavoriteItemUserMutex->auto_job( [&result]( ) {
	} );
	return result;
}
size_t MusicFavoriteItem::getMusicVectorClone( std::vector< IMusicItem * > &result_clone_vector ) const {
	size_t result;
	musicFavoriteItemUserMutex->auto_job( [&result, this, &result_clone_vector]( ) {
		result = musicItemVector.size( );
		result_clone_vector.resize( result );
		if( result ) {
			auto source = musicItemVector.data( );
			auto dest = result_clone_vector.data( );
			size_t index = 0;
			for( ; index < result; index += 1 )
				dest[ index ] = source[ index ];
		}
	} );
	return result;
}
void MusicFavoriteItem::setName( const QString &name ) {
	this->name = name;
}
IMusicCentreWidget * MusicFavoriteItem::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
IMusicFavoriteItemWidget * MusicFavoriteItem::getMusicFavoriteItemWidget( ) const {
	return musicFavoriteItemWidget;
}
MusicFavoriteItem::MusicFavoriteItem( ) {
	appendTypeInfo( this );
	musicFavoriteItemUserMutex = new UserMutex;
	musicFavoriteItemWidget = new MusicFavoriteItemWidget;
	bindMusicFavoriteItem( musicFavoriteItemWidget, this );
}
MusicFavoriteItem::~MusicFavoriteItem( ) {
	musicFavoriteItemUserMutex->lock( );
	musicItemVector.clear( );
	if( musicFavoriteItemWidget ) {
		delete musicFavoriteItemWidget;
	}
	musicFavoriteItemUserMutex->unlock( );
	delete musicFavoriteItemUserMutex;
	musicFavoriteItemUserMutex = nullptr;
}
