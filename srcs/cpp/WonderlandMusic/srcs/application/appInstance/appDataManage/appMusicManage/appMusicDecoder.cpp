#include "appMusicDecoder.h"

#include <QString>

#include <tools/stringTools.h>
#include <tools/vectorTools.h>

#include <head/extern_c.h>

#include <head/release_macro.h>

#include <musicPlayer/musicInfo.h>
#include <musicPlayer/musicInfoList.h>

#include <mutex/userMutex.h>

#include <tools/instanceTools.h>
#include <tools/invokeMethodTools.h>
#include <tools/pathTools.h>

#include "../../../../msgInfo/outDebug.h"

INCLUDE_EXTERN_C {
	#include <libavformat/avformat.h>
}

AppMusicDecoder::~AppMusicDecoder( ) {
	deleteResource( );
}

AppMusicDecoder::AppMusicDecoder( ) {
}

bool AppMusicDecoder::musicFileNmaeSupperDecoder( const QString &music_file_path ) const {
	size_t count = supperDecodeFileSuffix.size( );
	if( count == 0 )
		return false; // 没有正确解析后缀
	qsizetype indexOf = music_file_path.indexOf( "." );
	if( indexOf == -1 )
		return false; // 没有后缀
	auto compString = music_file_path.mid( indexOf + 1 );
	compString = compString.toUpper( );
	auto data = supperDecodeFileSuffix.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( *data[ index ] == compString )
			return true;
	return false;
}

AppMusicDecoder::StringOperator::StringOperator( ) {
	this->stringList = new QStringList;
}

AppMusicDecoder::StringOperator::~StringOperator( ) {
	delete stringList;
}

AppMusicDecoder::StringOperator & AppMusicDecoder::StringOperator::operator<<( const QString &append ) {
	*stringList << append;
	return *this;
}

void AppMusicDecoder::LoadMusic::connectLoadOverFinish( ) {
	QObject::connect( musicInfoList, &QThread::finished, [this]( ) {
		InvokeMethodTools::invokeQueuedConnectionMethod( [this] ( ApplicationManage *applicationManage ) {
			if( appMusicDecoder )
				if( LoadMusicDecoderTools::overLoad( appMusicDecoder, this ) )
					return;
			std::vector< MusicInfo * > musicInfos;
			musicInfoList->getOverLoadMusicVector( musicInfos );
			auto musicInfo = musicInfos.data( );
			size_t index = 0;
			size_t count = musicInfos.size( );
			for( ; index < count; index += 1 )
				delete musicInfo[ index ];
			delete this;
		} );
	} );
}
void AppMusicDecoder::LoadMusic::releaseAppMusicDecoder( ) {
	appMusicDecoder = nullptr;
}
AppMusicDecoder::LoadMusic::LoadMusic( AppMusicDecoder *app_music_decoder, IMusicFavoriteItem *music_favorite_item ) : musicFavoriteItem( music_favorite_item ), appMusicDecoder( app_music_decoder ) {
	musicInfoList = new MusicInfoList( );
	connectLoadOverFinish( );
}
AppMusicDecoder::LoadMusic::LoadMusic( AppMusicDecoder *app_music_decoder, IMusicFavoriteItem *music_favorite_item, const std::vector< QString > &file_list ) : appMusicDecoder( app_music_decoder ) {
	musicInfoList = new MusicInfoList( file_list );
	connectLoadOverFinish( );
}
AppMusicDecoder::LoadMusic::~LoadMusic( ) {
	musicInfoList->requestInterruption( );
	if( musicInfoList->isRunning( ) ) {
		auto sleepTime = std::chrono::microseconds( 100 );
		while( musicInfoList->isFinished( ) == false )
			std::this_thread::sleep_for( sleepTime );
	}
	if( appMusicDecoder )
		LoadMusicDecoderTools::overLoad( appMusicDecoder, this );
	delete musicInfoList;
}
bool AppMusicDecoder::LoadMusic::start( ) {
	musicInfoList->start( );
	return true;
}
bool AppMusicDecoder::LoadMusic::append( const std::vector< QString > &file_list ) {
	return musicInfoList->appendLoadMusicFileList( file_list );
}
bool AppMusicDecoder::LoadMusic::isRunning( ) {
	return musicInfoList->isRunning( );
}
bool AppMusicDecoder::LoadMusic::isFinished( ) {
	return musicInfoList->isFinished( );
}
MusicInfoList * AppMusicDecoder::LoadMusic::getMusicInfoList( ) const {
	return musicInfoList;
}
bool AppMusicDecoder::LoadMusic::moveToMusicInfoVector( std::vector< MusicInfo * > &result_detach_vector ) {
	return musicInfoList->moveToMusicInfoVector( result_detach_vector );
}
bool AppMusicDecoder::overLoad( LoadMusic *load_music ) {
	bool cond = false;
	LoadMusic *loadMusic;
	userMutex->lock( );
	size_t count = loadMusicVector.size( );
	auto data = loadMusicVector.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ] == load_music ) {
			loadMusic = data[ index ];
			OutDebug( ) << *loadMusic->getMusicInfoList( );
			loadMusicVector.erase( loadMusicVector.begin( ) + index );
			LoadMusicDecoderTools::releaseAppMusicDecoder( loadMusic );
			delete loadMusic;
			cond = true;
			break;
		}
	userMutex->unlock( );
	return cond;
}
void AppMusicDecoder::appendDecodeFileSuffix( const QString &decode_file_suffix ) {
	QString *newItemSuffixes = new QString( StringTools::getFileSuffix( decode_file_suffix ).toUpper( ) );
	supperDecodeFileSuffix.emplace_back( newItemSuffixes );
}

void AppMusicDecoder::appendDecodeFileSuffix( const QStringList &decode_file_suffix ) {
	auto count = decode_file_suffix.size( );
	if( count == 0 )
		return;
	auto data = decode_file_suffix.data( );
	decltype(count) index = 0;
	for( ; index < count; index += 1 )
		appendDecodeFileSuffix( data[ index ] );
}
bool AppMusicDecoder::init( ) {
	userMutex->lock( );
	void *opaque = nullptr;
	const AVOutputFormat *ofmt;
	QString buff;
	QStringList spliteStringList;
	qsizetype count;
	qsizetype index;
	QString *data;
	while( ( ofmt = av_muxer_iterate( &opaque ) ) != nullptr ) {
		if( ofmt->audio_codec == AV_CODEC_ID_NONE )
			continue;
		if( ofmt->extensions == nullptr || ofmt->extensions[ 0 ] == '\0' )
			continue;
		buff = QString::fromUtf8( ofmt->extensions );
		spliteStringList = buff.split( "," );
		count = spliteStringList.size( );
		data = spliteStringList.data( );
		for( index = 0; index < count; index += 1 )
			appendDecodeFileSuffix( data[ index ] );
	}
	userMutex->unlock( );
	return true;
}

bool AppMusicDecoder::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	return true;
}

bool AppMusicDecoder::initAfter( ) {
	return true;
}
bool AppMusicDecoder::loadMusicFile( IMusicFavoriteItem *music_favorite_item, const QString &music_file ) {
	userMutex->lock( );
	auto loadMusic = new LoadMusic( this, music_favorite_item, { music_file } );
	loadMusicVector.emplace_back( loadMusic );
	size_t result = loadMusic->start( ) ? 1 : 0;
	userMutex->unlock( );
	return result;
}
size_t AppMusicDecoder::loadMusicFile( IMusicFavoriteItem *music_favorite_item, const std::vector< QString > &music_file_path_vector ) {
	userMutex->lock( );
	size_t result = music_file_path_vector.size( );
	auto loadMusic = new LoadMusic( this, music_favorite_item, music_file_path_vector );
	loadMusicVector.emplace_back( loadMusic );
	loadMusic->start( );
	userMutex->unlock( );
	return result;
}
size_t AppMusicDecoder::loadMusicDir( IMusicFavoriteItem *music_favorite_item, const QString &music_dir_path ) {
	userMutex->lock( );
	size_t result = 0;

	QStringList filterMusicFileList;
	QStringList getFileList;
	if( PathTools::entryFilePath( filterMusicFileList, music_dir_path ) ) {
		result = PathTools::filterFile( getFileList, filterMusicFileList );
		if( result ) {
			result = PathTools::filterMusicFile( filterMusicFileList, getFileList );
			if( result ) {
				std::vector< QString > appendFile( result );
				auto data = appendFile.data( );
				size_t index = 0;
				auto pointer = filterMusicFileList.data( );
				for( ; index < result; index += 1 )
					data[ index ] = pointer[ index ];
				auto loadMusic = new LoadMusic( this, music_favorite_item, appendFile );
				loadMusicVector.emplace_back( loadMusic );
				loadMusic->start( );
			}
		}
	}
	userMutex->unlock( );
	return result;
}
bool AppMusicDecoder::startLoad( ) {
	return false;
}

bool AppMusicDecoder::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	VectorTools::deleteVectorPtr( supperDecodeFileSuffix );
	supperDecodeFileSuffix.clear( );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}

std::vector< QString > AppMusicDecoder::getSupperDecodeFileSuffix( ) const {
	userMutex->lock( );
	size_t count = supperDecodeFileSuffix.size( );
	std::vector< QString > result( count );
	auto data = supperDecodeFileSuffix.data( );
	auto resultData = result.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		resultData[ index ] = *data[ index ];
	userMutex->unlock( );
	return result;
}
bool LoadMusicDecoderTools::overLoad( AppMusicDecoder *app_music_decoder, AppMusicDecoder::LoadMusic *load_music ) {
	if( app_music_decoder == nullptr || load_music == nullptr )
		return false;
	return app_music_decoder->overLoad( load_music );
}
void LoadMusicDecoderTools::releaseAppMusicDecoder( AppMusicDecoder::LoadMusic *load_music ) {
	if( load_music )
		load_music->releaseAppMusicDecoder( );
}
