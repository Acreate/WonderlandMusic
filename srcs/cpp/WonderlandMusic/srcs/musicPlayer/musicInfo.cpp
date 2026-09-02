#include "musicInfo.h"

#include <QFileInfo>

#include <mutex/userMutex.h>

#include "../head/extern_c.h"

INCLUDE_EXTERN_C {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/avutil.h>
	#include <libavutil/dict.h>
}

MusicInfo::MusicInfo( const QString &file_path ) {
	userMutex = new UserMutex;
	fileInfo = new QFileInfo( file_path );
	status = RunStatus::Ready;
	fmtCtx = nullptr;
	filePath = fileInfo->absoluteFilePath( );
}
MusicInfo::~MusicInfo( ) {
	QThread::requestInterruption( );
	auto sleepTime = std::chrono::milliseconds( 1000 );
	while( isRunning( ) )
		std::this_thread::sleep_for( sleepTime );
	if( fmtCtx )
		avformat_close_input( &fmtCtx );
	delete fileInfo;
	delete userMutex;
	userMutex = nullptr;
}
void MusicInfo::run( ) {
	// 跳出宏
	#define Is_Interruption_Requested( ) if( isInterruptionRequested( ) ) break
	userMutex->lock( );
	do {
		if( fileInfo->exists( ) == false || status == RunStatus::Run )
			break;
		status = RunStatus::Run;
		if( fmtCtx )
			avformat_close_input( &fmtCtx );
		Is_Interruption_Requested( );
		// 打开
		int ret = avformat_open_input( &fmtCtx, filePath.toStdString( ).c_str( ), nullptr, nullptr );
		if( ret < 0 )
			break;
		Is_Interruption_Requested( );
		int formatFindInfo = avformat_find_stream_info( fmtCtx, NULL );
		if( formatFindInfo < 0 )
			break;
		Is_Interruption_Requested( );
		// 查找音频流索引
		int audioStreamIndex = av_find_best_stream( fmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0 );
		if( audioStreamIndex < 0 )
			break;
		Is_Interruption_Requested( );
		AVStream *audioStream = fmtCtx->streams[ audioStreamIndex ];
		AVCodecParameters *codecPar = audioStream->codecpar;

		AVSampleFormat sampleFmt;
		AVCodecID avCodecId;

		avCodecId = codecPar->codec_id;
		avcodecGetName = avcodec_get_name( avCodecId );
		sampleRate = codecPar->sample_rate;
		nbChannels = codecPar->ch_layout.nb_channels;
		sampleFmt = ( AVSampleFormat ) codecPar->format;
		avGetSampleFmtName = av_get_sample_fmt_name( sampleFmt );

		Is_Interruption_Requested( );

		bitRate = codecPar->bit_rate;
		durationUs = audioStream->duration;
		if( durationUs == AV_NOPTS_VALUE )
			durationUs = fmtCtx->duration;

		durationSec = ( double ) durationUs / AV_TIME_BASE;
		char chBuf[ 1024 ] { 0 };
		av_channel_layout_describe( &codecPar->ch_layout, chBuf, sizeof( chBuf ) );
		channelLayoutDescribe = QString( chBuf );

		Is_Interruption_Requested( );

		AVDictionary *meta = fmtCtx->metadata;
		if( !meta )
			break;
		AVDictionaryEntry *entry = nullptr;

		auto get_val = [&] ( const char *key ) ->QString {
			entry = av_dict_get( meta, key, nullptr, AV_DICT_IGNORE_SUFFIX );
			if( entry && entry->value )
				return QString( entry->value );
			return "";
		};

		title = get_val( "title" );
		artist = get_val( "artist" );
		album = get_val( "album" );
		albumArtist = get_val( "album_artist" );
		genre = get_val( "genre" );
		date = get_val( "date" );
		track = get_val( "track" );
		comment = get_val( "comment" );
	} while( false );
	if( fmtCtx )
		avformat_close_input( &fmtCtx );
	status = RunStatus::Over;
	userMutex->unlock( );
}
bool MusicInfo::isRead( ) const {
	if( status != RunStatus::Ready )
		return false;
	userMutex->lock( );
	if( fileInfo->exists( ) == false )
		return userMutex->result_unlock( false );
	return userMutex->result_unlock( true );
}
const QString & MusicInfo::getFilePath( ) const {
	return filePath;
}

MusicInfo::RunStatus MusicInfo::getStatus( ) const {
	return status;
}
const QString & MusicInfo::getTitle( ) const {
	return title;
}
const QString & MusicInfo::getArtist( ) const {
	return artist;
}
const QString & MusicInfo::getAlbum( ) const {
	return album;
}
const QString & MusicInfo::getAlbumArtist( ) const {
	return albumArtist;
}
const QString & MusicInfo::getGenre( ) const {
	return genre;
}
const QString & MusicInfo::getDate( ) const {
	return date;
}
const QString & MusicInfo::getTrack( ) const {
	return track;
}
const QString & MusicInfo::getComment( ) const {
	return comment;
}
const QString & MusicInfo::getAvcodecGetName( ) const {
	return avcodecGetName;
}
int MusicInfo::getSampleRate( ) const {
	return sampleRate;
}
int MusicInfo::getNbChannels( ) const {
	return nbChannels;
}
const QString & MusicInfo::getAvGetSampleFmtName( ) const {
	return avGetSampleFmtName;
}
int64_t MusicInfo::getBitRate( ) const {
	return bitRate;
}
int64_t MusicInfo::getDurationUs( ) const {
	return durationUs;
}
double MusicInfo::getDurationSec( ) const {
	return durationSec;
}
const QString & MusicInfo::getChannelLayoutDescribe( ) const {
	return channelLayoutDescribe;
}
