#include "musicFileInfoList.h"

#include "musicFileInfo.h"

#include <mutex/userMutex.h>

#include "../application/appInstance/applicationManage.h"

#include "../head/result_message_out.h"

#include "../tools/invokeMethodTools.h"
#include "../tools/templateArgs.h"
void MusicFileInfoList::overWork( ) {
	InvokeMethodTools::invokeQueuedConnectionMethod( [this] ( ApplicationManage *applicationManage ) {
		userMutex->lock( );
		if( current == nullptr ) {
			Result_Var_Function_Messag_Ptr_Out_Args( false, this, overWork, tr( "接受到非已方工作" ) );
			userMutex->unlock( );
			emit signal_finish( this );
			return;
		}
		if( current->isInterruptionRequested( ) ) {
			userMutex->unlock( );
			emit signal_finish( this );
			return;
		}
		for( index = 0; index < count; index += 1 )
			if( musicVectorDataPtr[ index ] == current ) {
				overLoadMusicVector.emplace_back( current );
				musicVectorDataPtr[ index ] = nullptr;
				size_t overCount = overLoadMusicVector.size( );
				if( count == overCount ) { // 完成所有人物
					musicVector.clear( );
					musicVectorDataPtr = musicVector.data( );
					count = 0;
					current = nullptr;
					status = Status::Finish;
					userMutex->unlock( );
					emit signal_finish( this );
					return;
				}

				if( current->isInterruptionRequested( ) ) {
					userMutex->unlock( );
					emit signal_finish( this );
					return;
				}
				overCount = index;
				for( index += 1; index < count; index += 1 ) // 从后续查找任务
					if( musicVectorDataPtr[ index ] && musicVectorDataPtr[ index ]->isReady( ) ) {
						current = musicVectorDataPtr[ index ];
						current->start( );
						userMutex->unlock( );
						emit signal_start( this );
						return;
					}
				if( current->isInterruptionRequested( ) ) {
					userMutex->unlock( );
					emit signal_finish( this );
					return;
				}
				for( index = 0; index < overCount; index += 1 ) // 重新开始匹配任务
					if( musicVectorDataPtr[ index ] && musicVectorDataPtr[ index ]->isReady( ) ) {
						current = musicVectorDataPtr[ index ];
						current->start( );
						userMutex->unlock( );
						emit signal_start( this );
						return;
					}
				userMutex->unlock( );
				emit signal_finish( this );
				return;
			}
		userMutex->unlock( );
		if( current->isInterruptionRequested( ) ) {
			emit signal_finish( this );
			return;
		}
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
		connect( musicInfo, &MusicFileInfo::finished, this, &MusicFileInfoList::overWork );
	}
}
MusicFileInfoList::MusicFileInfoList( ) : QObject( ) {
	userMutex = new UserMutex;
	count = 0;
	musicVectorDataPtr = nullptr;
	status = Status::None;
	interruption = false;
	current = nullptr;
}
MusicFileInfoList::~MusicFileInfoList( ) {
	if( isRunning( ) ) {
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
	if( isFinished( ) || isInterruptionRequested( ) || count != 0 )
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
		connect( musicInfo, &MusicFileInfo::finished, this, &MusicFileInfoList::overWork );
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
	if( isFinished( ) == false )
		return userMutex->result_unlock( false );
	result_detach_vector = overLoadMusicVector;
	result_detach_vector.append_range( musicVector );
	overLoadMusicVector.clear( );
	musicVector.clear( );
	userMutex->unlock( );
	return true;
}
bool MusicFileInfoList::requestInterruption( ) {
	if( current == nullptr )
		return false;
	current->requestInterruption( );
	return true;
}
bool MusicFileInfoList::isFinished( ) const {
	return status == Status::Finish && current == nullptr;
}
bool MusicFileInfoList::isRunning( ) const {
	return status == Status::Run && current;
}
bool MusicFileInfoList::isInterruptionRequested( ) const {
	if( current == nullptr )
		return false;
	return current->isInterruptionRequested( );
}
bool MusicFileInfoList::start( ) {
	userMutex->lock( );
	if( current ) {
		userMutex->unlock( );
		emit signal_finish( this );
		return false;
	}
	status = Status::None;
	for( index = 0; index < count; index += 1 )
		if( musicVectorDataPtr[ index ]->isReady( ) ) {
			status = Status::Run;
			current = musicVectorDataPtr[ index ];
			current->start( );
			userMutex->unlock( );
			emit signal_start( this );
			return true;
		}
	userMutex->unlock( );
	emit signal_finish( this );
	return false;
}
MusicFileInfoList::Status MusicFileInfoList::getStatus( ) const {
	return status;
}
