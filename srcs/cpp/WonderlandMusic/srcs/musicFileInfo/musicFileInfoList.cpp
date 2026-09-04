#include "musicFileInfoList.h"

#include "musicFileInfo.h"

#include <mutex/userMutex.h>

#include "../application/appInstance/applicationManage.h"

#include "../tools/invokeMethodTools.h"
#include "../tools/templateArgs.h"
void MusicFileInfoList::loadFinished( MusicFileInfo *music_info ) {
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

MusicFileInfoList::MusicFileInfoList( const std::vector< QString > &file_list ) : MusicFileInfoList( ) {
	count = file_list.size( );
	musicVector.resize( count );
	auto sourceDataPtr = file_list.data( );
	musicVectorDataPtr = musicVector.data( );
	MusicFileInfo *musicInfo;
	QString filePath;
	for( index = 0; index < count; index += 1 ) {
		filePath = sourceDataPtr[ index ];
		musicInfo = new MusicFileInfo( filePath );
		musicVectorDataPtr[ index ] = musicInfo;
		connect( musicInfo, &MusicFileInfo::finished, [musicInfo, this]( ) {
			loadFinished( musicInfo );
		} );
	}
}
MusicFileInfoList::MusicFileInfoList( ) : QThread( ) {
	userMutex = new UserMutex;
	count = 0;
	musicVectorDataPtr = nullptr;
}
MusicFileInfoList::~MusicFileInfoList( ) {
	if( isRunning( ) == true ) {
		requestInterruption( );
		auto sleepTime = std::chrono::microseconds( 500 );
		while( isFinished( ) == false )
			std::this_thread::sleep_for( sleepTime );
	}
	userMutex->lock( );
	size_t overCount = overLoadMusicVector.size( );
	auto musicInfo = overLoadMusicVector.data( );
	for( index = 0; index < overCount; index += 1 )
		if( musicInfo[ index ] )
			delete musicInfo[ index ];
	for( index = 0; index < count; index += 1 )
		if( musicVectorDataPtr[ index ] )
			delete musicVectorDataPtr[ index ];
	overLoadMusicVector.clear( );
	musicVector.clear( );
	count = 0;
	userMutex->unlock( );
	delete userMutex;
	userMutex = nullptr;
}
bool MusicFileInfoList::appendLoadMusicFileList( const std::vector< QString > &file_list ) {
	userMutex->lock( );
	if( isFinished( ) || isInterruptionRequested( ) || count == overLoadMusicVector.size( ) )
		return userMutex->result_unlock( false );
	size_t appendCount = file_list.size( );
	size_t newCount = appendCount + count;
	std::vector< MusicFileInfo * > buff( newCount, nullptr );
	auto buffData = buff.data( );
	for( index = 0; index < count; index += 1 )
		buffData[ index ] = musicVectorDataPtr[ index ];

	auto sourceDataPtr = file_list.data( );
	MusicFileInfo *musicInfo;
	QString filePath;
	for( index = 0; index < count; index += 1 ) {
		filePath = sourceDataPtr[ index ];
		musicInfo = new MusicFileInfo( filePath );
		buffData[ index + count ] = musicInfo;
		connect( musicInfo, &MusicFileInfo::finished, [musicInfo, this]( ) {
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
bool MusicFileInfoList::getOverLoadMusicVector( std::vector< MusicFileInfo * > &result_over_load_music_info_vector ) const {
	userMutex->lock( );
	if( 0 != count )
		return userMutex->result_unlock( false );
	result_over_load_music_info_vector = overLoadMusicVector;
	return userMutex->result_unlock( true );
}
QStringList MusicFileInfoList::toQStringList( ) const {
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
MusicFileInfoList::operator QString( ) const {
	return toQStringList( ).join( "" );
}
size_t MusicFileInfoList::getCount( ) const {
	return count;
}
bool MusicFileInfoList::moveToMusicInfoVector( std::vector< MusicFileInfo * > &result_detach_vector ) {
	userMutex->lock( );
	if( isRunning( ) == true || isFinished( ) == false )
		return userMutex->result_unlock( false );
	result_detach_vector = overLoadMusicVector;
	result_detach_vector.append_range( musicVector );
	overLoadMusicVector.clear( );
	musicVector.clear( );
	userMutex->unlock( );
	return true;
}

void MusicFileInfoList::run( ) {
	userMutex->lock( );
	for( index = 0; index < count; index += 1 )
		if( musicVectorDataPtr[ index ]->isRead( ) )
			musicVectorDataPtr[ index ]->start( );
	userMutex->unlock( );
	auto sleepTime = std::chrono::milliseconds( 500 );
	while( count != 0 )
		std::this_thread::sleep_for( sleepTime );
}
