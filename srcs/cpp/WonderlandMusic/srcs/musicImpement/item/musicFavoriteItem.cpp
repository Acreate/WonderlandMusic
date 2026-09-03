#include "musicFavoriteItem.h"

#include <qimage.h>

#include <application/appInstance/appDataManage.h>

#include <component/musicWindow/interface/item/iMusicItem.h>

#include <mutex/userMutex.h>

#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>

#include <musicImpement/itemWidget/musicFavoriteItemWidget.h>

#include "../../component/musicWindow/interface/ItemWidget/iMusicItemWidget.h"

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
	musicItemVector.emplace_back( music_item );
	musicFavoriteItemUserMutex->unlock( );
	if( musicCentreWidget )
		musicCentreWidget->repaintListWidget( );
	return true;
}
bool MusicFavoriteItem::addMusicItem( const std::vector< IMusicItem * > &music_info_items ) {
	musicFavoriteItemUserMutex->lock( );
	musicItemVector.append_range( music_info_items );
	musicFavoriteItemUserMutex->unlock( );
	if( musicCentreWidget )
		musicCentreWidget->repaintListWidget( );
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
bool MusicFavoriteItem::fromYPosGetMusicItem( IMusicItem *&result_music_item, const size_t &y_pos ) const {
	musicFavoriteItemUserMutex->lock( );

	size_t count = musicItemVector.size( );
	if( count ) {
		size_t index = 0;
		auto musicItem = musicItemVector.data( );
		IMusicItemWidget *musicItemWidget;
		QWidget *widget;
		for( ; index < count; index += 1 ) {
			musicItemWidget = musicItem[ index ]->getMusicItemWidget( );
			if( musicItemWidget == nullptr )
				continue;
			widget = musicItemWidget->toWidget( );
			if( widget == nullptr )
				continue;
			if( widget->geometry( ).contains( 1, y_pos ) )
				break;
			result_music_item = musicItem[ index ];
			return musicFavoriteItemUserMutex->result_unlock( true );
		}
	}
	return musicFavoriteItemUserMutex->result_unlock( false );
}
bool MusicFavoriteItem::fromIndexGetMusicItem( IMusicItem *&result_music_item, const size_t &index ) const {
	musicFavoriteItemUserMutex->lock( );

	size_t count = musicItemVector.size( );
	if( count > index ) {
		auto musicItem = musicItemVector.data( );
		result_music_item = musicItem[ index ];
		return musicFavoriteItemUserMutex->result_unlock( true );
	}

	return musicFavoriteItemUserMutex->result_unlock( false );
}
bool MusicFavoriteItem::fromMusicItemGetIndex( size_t &result_index, const IMusicItem *music_item ) const {
	musicFavoriteItemUserMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		auto musicItem = musicItemVector.data( );
		for( result_index = 0; result_index < count; result_index += 1 )
			if( musicItem[ result_index ] == music_item )
				return musicFavoriteItemUserMutex->result_unlock( true );
	}
	return musicFavoriteItemUserMutex->result_unlock( false );
}
bool MusicFavoriteItem::fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &music_name ) const {
	musicFavoriteItemUserMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		auto musicItem = musicItemVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( musicItem[ index ]->getName( ) == music_name ) {
				result_music_item = musicItem[ index ];
				return musicFavoriteItemUserMutex->result_unlock( true );
			}
	}
	return musicFavoriteItemUserMutex->result_unlock( false );
}
bool MusicFavoriteItem::fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) const {
	musicFavoriteItemUserMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		auto musicItem = musicItemVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( musicItem[ index ]->getFileBaseName( ) == file_base_name ) {
				result_music_item = musicItem[ index ];
				return musicFavoriteItemUserMutex->result_unlock( true );
			}
	}
	return musicFavoriteItemUserMutex->result_unlock( false );
}
bool MusicFavoriteItem::fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &absolute_file_path ) const {
	musicFavoriteItemUserMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		auto musicItem = musicItemVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( musicItem[ index ]->getAbsoluteFilePath( ) == absolute_file_path ) {
				result_music_item = musicItem[ index ];
				return musicFavoriteItemUserMutex->result_unlock( true );
			}
	}
	return musicFavoriteItemUserMutex->result_unlock( false );
}
bool MusicFavoriteItem::fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) const {
	musicFavoriteItemUserMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		auto musicItem = musicItemVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( musicItem[ index ]->getSinger( ) == singer ) {
				result_music_item = musicItem[ index ];
				return musicFavoriteItemUserMutex->result_unlock( true );
			}
	}
	return musicFavoriteItemUserMutex->result_unlock( false );
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
	musicFavoriteItemUserMutex->lock( );
	this->name = name;
	musicFavoriteItemUserMutex->unlock( );
	if( musicFavoriteItemWidget )
		musicFavoriteItemWidget->updateLayout( );
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
