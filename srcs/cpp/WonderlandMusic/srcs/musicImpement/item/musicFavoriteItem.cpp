#include "musicFavoriteItem.h"

#include <qimage.h>

#include <application/appInstance/appDataManage.h>

#include <component/musicWindow/interface/item/iMusicItem.h>

#include <mutex/userMutex.h>

#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>

#include <musicImpement/itemWidget/musicFavoriteItemWidget.h>

#include <component/musicWindow/musicWindow.h>
#include <component/musicWindow/interface/ItemWidget/iMusicItemWidget.h>

#include "musicInfoItem.h"

#include "../../application/appInstance/appDataManage/appMusicManage.h"

#include "../../musicPlayer/musicInfo.h"

#include "../../tools/instanceTools.h"
#include "../../tools/invokeMethodTools.h"
#include "../../tools/pathTools.h"

bool MusicFavoriteItem::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicFavoriteItemUserMutex->lock( );
	musicCentreWidget = music_centre_widget;
	musicFavoriteItemUserMutex->unlock( );
	return true;
}
MusicInfoItem * MusicFavoriteItem::load( MusicInfo *music_info ) {
	auto musicItem = new MusicInfoItem( this, *music_info );
	musicFavoriteItemUserMutex->lock( );
	musicItemVector.emplace_back( musicItem );
	musicFavoriteItemUserMutex->unlock( );
	if( musicCentreWidget )
		musicCentreWidget->repaintListWidget( );
	return musicItem;
}
bool MusicFavoriteItem::getName( QString &result_name ) const {
	musicFavoriteItemUserMutex->lock( );
	result_name = name;
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
bool MusicFavoriteItem::loadMusicDirPath( const std::vector< QString > &music_file_path ) {
	size_t result = 0;
	QStringList filterMusicFileList;
	QStringList getFileList;
	if( PathTools::entryFilePath( filterMusicFileList, music_file_path ) ) {
		result = PathTools::filterFile( getFileList, filterMusicFileList );
		if( result ) {
			result = PathTools::filterMusicFile( filterMusicFileList, getFileList );
			if( result ) {
				size_t index = 0;
				auto pointer = filterMusicFileList.data( );
				for( ; index < result; index += 1 ) {
					auto musicInfo = new MusicInfo( pointer[ index ] );
					if( musicInfo == nullptr )
						return false;
					connect( musicInfo, &MusicInfo::finished, [this, musicInfo]( ) {
						InvokeMethodTools::invokeQueuedConnectionMethod( [this, musicInfo] ( ApplicationManage *applicationManage ) {
							load( musicInfo );
							delete musicInfo;
						} );
					} );
					musicInfo->start( );
				}
			}
		}
	}
	return result;
}
bool MusicFavoriteItem::loadMusicFile( const std::vector< QString > &music_file_path ) {
	auto appMusicManage = InstanceTools::getAppMusicManage( );
	if( appMusicManage == nullptr )
		return false;
	size_t count = music_file_path.size( );
	if( count == 0 )
		return false;
	auto data = music_file_path.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( appMusicManage->musicFileNameSupperDecoder( data[ index ] ) ) {
			auto musicInfo = new MusicInfo( data[ index ] );
			if( musicInfo == nullptr )
				return false;
			connect( musicInfo, &MusicInfo::finished, [this, musicInfo]( ) {
				InvokeMethodTools::invokeQueuedConnectionMethod( [this, musicInfo] ( ApplicationManage *applicationManage ) {
					load( musicInfo );
					delete musicInfo;
				} );
			} );
			musicInfo->start( );
		}
	return true;
}
bool MusicFavoriteItem::loadMusicFile( const QString &music_file_path ) {
	if( PathTools::isMusicFile( music_file_path ) == false )
		return false;
	auto musicInfo = new MusicInfo( music_file_path );
	if( musicInfo == nullptr )
		return false;
	connect( musicInfo, &MusicInfo::finished, [this, musicInfo]( ) {
		InvokeMethodTools::invokeQueuedConnectionMethod( [this, musicInfo] ( ApplicationManage *applicationManage ) {
			load( musicInfo );
			delete musicInfo;
		} );
	} );
	musicInfo->start( );
	return true;
}
MusicFavoriteItem::MusicFavoriteItem( ) {
	appendTypeInfo( this );
	musicFavoriteItemUserMutex = new UserMutex;
	musicFavoriteItemWidget = new MusicFavoriteItemWidget;
	bindMusicFavoriteItem( musicFavoriteItemWidget, this );
}
MusicFavoriteItem::~MusicFavoriteItem( ) {
	musicFavoriteItemUserMutex->lock( );
	size_t count = musicItemVector.size( );
	if( count ) {
		size_t index = 0;
		auto data = musicItemVector.data( );
		for( ; index < count; index += 1 ) {
			setMusicItemFavoriteItem( data[ index ], nullptr );
			delete data[ index ];
		}
	}
	musicItemVector.clear( );
	if( musicFavoriteItemWidget )
		delete musicFavoriteItemWidget;
	musicFavoriteItemWidget = nullptr;
	musicFavoriteItemUserMutex->unlock( );
	delete musicFavoriteItemUserMutex;
	musicFavoriteItemUserMutex = nullptr;
}
