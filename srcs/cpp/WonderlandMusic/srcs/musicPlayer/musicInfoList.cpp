#include "musicInfoList.h"

#include "musicInfo.h"

#include <mutex/userMutex.h>

#include "../application/appInstance/applicationManage.h"

#include "../tools/invokeMethodTools.h"
#include "../tools/templateArgs.h"
void MusicInfoList::loadFinished( MusicInfo *music_info ) {
	if( music_info == nullptr )
		return;
	bool isRelease = true;
	userMutex->lock( );
	for( index = 0; index < count; index += 1 )
		if( musicVectorDataPtr[ index ] == music_info ) {
			overLoadMusicVector.emplace_back( musicVectorDataPtr[ index ] );
			musicVectorDataPtr[ index ] = nullptr;
			isRelease = false;
			if( count == overLoadMusicVector.size( ) ) {
				musicVector.clear( );
				musicVectorDataPtr = musicVector.data( );
				count = 0;
				break;
			}
			break;
		}
	userMutex->unlock( );
	if( isRelease )
		InvokeMethodTools::invokeQueuedConnectionMethod( [music_info] ( ApplicationManage *applicationManage ) {
			delete music_info;
		} );
}

MusicInfoList::MusicInfoList( const std::vector< QString > &file_list ) : MusicInfoList( ) {
	count = file_list.size( );
	musicVector.resize( count );
	auto sourceDataPtr = file_list.data( );
	musicVectorDataPtr = musicVector.data( );
	MusicInfo *musicInfo;
	QString filePath;
	for( index = 0; index < count; index += 1 ) {
		filePath = sourceDataPtr[ index ];
		musicInfo = new MusicInfo( filePath );
		musicVectorDataPtr[ index ] = musicInfo;
		connect( musicInfo, &MusicInfo::finished, [musicInfo, this]( ) {
			loadFinished( musicInfo );
		} );
	}
}
MusicInfoList::MusicInfoList( ) : QThread( ) {
	userMutex = new UserMutex;
	count = 0;
	musicVectorDataPtr = nullptr;
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
	userMutex = nullptr;
}
bool MusicInfoList::appendLoadMusicFileList( const std::vector< QString > &file_list ) {
	userMutex->lock( );
	if( isFinished( ) || isInterruptionRequested( ) || count == overLoadMusicVector.size( ) )
		return userMutex->result_unlock( false );
	size_t appendCount = file_list.size( );
	size_t newCount = appendCount + count;
	std::vector< MusicInfo * > buff( newCount, nullptr );
	auto buffData = buff.data( );
	for( index = 0; index < count; index += 1 )
		buffData[ index ] = musicVectorDataPtr[ index ];

	auto sourceDataPtr = file_list.data( );
	MusicInfo *musicInfo;
	QString filePath;
	for( index = 0; index < count; index += 1 ) {
		filePath = sourceDataPtr[ index ];
		musicInfo = new MusicInfo( filePath );
		buffData[ index + count ] = musicInfo;
		connect( musicInfo, &MusicInfo::finished, [musicInfo, this]( ) {
			loadFinished( musicInfo );
		} );
		if( isRunning( ) )
			musicInfo->start( );
	}
	musicVector = buff;
	count = newCount;
	musicVectorDataPtr = musicVector.data( );
	userMutex->unlock( );
	return true;
}
bool MusicInfoList::getOverLoadMusicVector( std::vector< MusicInfo * > &result_over_load_music_info_vector ) const {
	userMutex->lock( );
	if( 0 != count )
		return userMutex->result_unlock( false );
	result_over_load_music_info_vector = overLoadMusicVector;
	return userMutex->result_unlock( true );
}
QStringList MusicInfoList::toQStringList( ) const {
	QString musicInfoStringList;
	QString overLoadMusicInfoStringList;

	size_t loadOverCount;
	loadOverCount = overLoadMusicVector.size( );
	QString currentMusicInfoVectorString;
	QString loadOverCountString;
	QString classNameString = QString( "class %1 {\n" ).arg( TemplateArgs::getTypeName( this ) );
	userMutex->lock( );
	currentMusicInfoVectorString = QString( "\tcount := %1 ;\n" ).arg( QString::number( count ) );
	loadOverCountString = QString( "\tloadOverCount := %1 ;\n" ).arg( QString::number( loadOverCount ) );
	size_t loadOverIndex;
	if( count ) {
		for( loadOverIndex = 0; loadOverIndex < count; loadOverIndex += 1 )
			if( musicVectorDataPtr[ loadOverIndex ] )
				musicInfoStringList.append( QString( "\t[ %1 ] := " ).arg( loadOverIndex ) ).append( musicVectorDataPtr[ loadOverIndex ]->toQStringList( ).join( "\t" ) ).append( "\n" );
	}
	auto musicInfo = overLoadMusicVector.data( );
	for( loadOverIndex = 0; loadOverIndex < loadOverCount; loadOverIndex += 1 )
		if( musicInfo[ loadOverIndex ] )
			overLoadMusicInfoStringList.append( QString( "\t[ %1 ] := " ).arg( loadOverIndex ) ).append( musicInfo[ loadOverIndex ]->toQStringList( ).join( "\t" ) ).append( "\n" );
	userMutex->unlock( );
	QStringList result;
	result.append( classNameString );
	result.append( currentMusicInfoVectorString );
	result.append( musicInfoStringList );
	result.append( loadOverCountString );
	result.append( overLoadMusicInfoStringList );
	result.append( "};" );
	return result;
}
MusicInfoList::operator QString( ) const {
	return toQStringList( ).join( "" );
}
size_t MusicInfoList::getCount( ) const {
	return count;
}
void MusicInfoList::run( ) {
	userMutex->lock( );
	for( index = 0; index < count; index += 1 )
		if( musicVectorDataPtr[ index ]->isRead( ) )
			musicVectorDataPtr[ index ]->start( );
	userMutex->unlock( );
	auto sleepTime = std::chrono::milliseconds( 500 );
	while( count != 0 )
		std::this_thread::sleep_for( sleepTime );
}
