#include "musicFileInfo.h"

#include <QFileInfo>

#include <mutex/userMutex.h>

#include "../dateTimeFormat/dateTimeFormat.h"

#include "../head/extern_c.h"
#include "../head/result_message_out.h"

#include "../tools/templateArgs.h"

INCLUDE_EXTERN_C {
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/avutil.h>
	#include <libavutil/dict.h>
}

static bool getAudioInfo( QString &result, AVDictionary *meta, const char *key );

MusicFileInfo::MusicFileInfo( const QString &file_path ) {
	musicStatus = -1;
	userMutex = new UserMutex;
	fileInfo = new QFileInfo( file_path );
	status = RunStatus::Ready;
	absoluteFilePath = fileInfo->absoluteFilePath( );
	filePath = fileInfo->fileName( );
	fileBaseName = fileInfo->baseName( );
}
MusicFileInfo::~MusicFileInfo( ) {
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
MusicFileInfo::MusicFileInfo( const MusicFileInfo &other ) {
	operator=( other );
}
MusicFileInfo & MusicFileInfo::operator=( const MusicFileInfo &other ) {
	if( this == &other )
		return *this;
	status = other.status;
	filePath = other.filePath;
	absoluteFilePath = other.absoluteFilePath;
	title = other.title;
	artist = other.artist;
	album = other.album;
	albumArtist = other.albumArtist;
	genre = other.genre;
	date = other.date;
	track = other.track;
	comment = other.comment;
	avcodecGetName = other.avcodecGetName;
	sampleRate = other.sampleRate;
	nbChannels = other.nbChannels;
	avGetSampleFmtName = other.avGetSampleFmtName;
	bitRate = other.bitRate;
	durationMillsecond = other.durationMillsecond;
	durationMillsecondDateTimeString = other.durationMillsecondDateTimeString;
	channelLayoutDescribe = other.channelLayoutDescribe;
	fileBaseName = other.fileBaseName;
	if( userMutex == nullptr )
		userMutex = new UserMutex;
	if( fileInfo )
		fileInfo = new QFileInfo( absoluteFilePath );
	if( fmtCtx )
		avformat_close_input( &fmtCtx );
	fmtCtx = nullptr;
	musicStatus = other.musicStatus;
	return *this;
}
void MusicFileInfo::run( ) {
	// 跳出宏
	#define Is_Interruption_Requested( ) if( isInterruptionRequested( ) ) break
	userMutex->lock( );
	do {
		musicStatus = 1;
		if( fileInfo->exists( ) == false || status == RunStatus::Run )
			break;
		status = RunStatus::Run;
		if( fmtCtx )
			avformat_close_input( &fmtCtx );
		Is_Interruption_Requested( );
		// 打开
		int ret = avformat_open_input( &fmtCtx, absoluteFilePath.toStdString( ).c_str( ), nullptr, nullptr );
		if( ret < 0 ) {
			char err_buf[ AV_ERROR_MAX_STRING_SIZE ] = { 0 };
			av_strerror( ret, err_buf, sizeof( err_buf ) );
			Result_Var_Function_Messag_Ptr_Out_Args( false, fmtCtx, avformat_open_input, tr( "%1 : [%1]" ).arg( QString(err_buf) ).arg( absoluteFilePath) );
			break;
		}
		Is_Interruption_Requested( );
		int formatFindInfo = avformat_find_stream_info( fmtCtx, NULL );
		if( formatFindInfo < 0 ) {
			char err_buf[ AV_ERROR_MAX_STRING_SIZE ] = { 0 };
			av_strerror( formatFindInfo, err_buf, sizeof( err_buf ) );
			Result_Var_Function_Messag_Ptr_Out_Args( false, fmtCtx, avformat_find_stream_info, tr( "%1 : [%1]" ).arg( QString(err_buf) ).arg( absoluteFilePath) );
			break;
		}
		Is_Interruption_Requested( );
		// 查找音频流索引
		int audioStreamIndex = av_find_best_stream( fmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0 );
		if( audioStreamIndex < 0 ) {
			Result_Var_Function_Messag_Ptr_Out_Args( false, fmtCtx, av_find_best_stream, tr( "不存在任何音频流 : [%1]" ).arg( absoluteFilePath) );
			break;
		}
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
		durationMillsecond = audioStream->duration * 1000 * av_q2d( audioStream->time_base );
		durationMillsecondDateTimeString = DateTimeFormat::millsecondToHourMinSecFrom( durationMillsecond );
		char chBuf[ 1024 ] { 0 };
		av_channel_layout_describe( &codecPar->ch_layout, chBuf, sizeof( chBuf ) );
		channelLayoutDescribe = QString( chBuf );

		Is_Interruption_Requested( );

		AVDictionary *meta = fmtCtx->metadata;
		if( !meta )
			break;
		getAudioInfo( title, meta, "title" );
		Is_Interruption_Requested( );
		getAudioInfo( artist, meta, "artist" );
		Is_Interruption_Requested( );
		getAudioInfo( album, meta, "album" );
		Is_Interruption_Requested( );
		getAudioInfo( albumArtist, meta, "album_artist" );
		Is_Interruption_Requested( );
		getAudioInfo( genre, meta, "genre" );
		Is_Interruption_Requested( );
		getAudioInfo( date, meta, "date" );
		Is_Interruption_Requested( );
		getAudioInfo( track, meta, "track" );
		Is_Interruption_Requested( );
		getAudioInfo( comment, meta, "comment" );
		musicStatus = 0;
	} while( false );
	if( fmtCtx )
		avformat_close_input( &fmtCtx );
	status = RunStatus::Over;
	userMutex->unlock( );
}
bool MusicFileInfo::isOK( ) const {
	return musicStatus == 0;
}
bool MusicFileInfo::isRead( ) const {
	if( status != RunStatus::Ready )
		return false;
	userMutex->lock( );
	if( fileInfo->exists( ) == false )
		return userMutex->result_unlock( false );
	return userMutex->result_unlock( true );
}
const QString & MusicFileInfo::getFileBaseName( ) const {
	return fileBaseName;
}
const QString & MusicFileInfo::getFilePath( ) const {
	return filePath;
}
const QString & MusicFileInfo::getAbsoluteFilePath( ) const {
	return absoluteFilePath;
}

MusicFileInfo::RunStatus MusicFileInfo::getStatus( ) const {
	return status;
}
const QString & MusicFileInfo::getTitle( ) const {
	return title;
}
const QString & MusicFileInfo::getArtist( ) const {
	return artist;
}
const QString & MusicFileInfo::getAlbum( ) const {
	return album;
}
const QString & MusicFileInfo::getAlbumArtist( ) const {
	return albumArtist;
}
const QString & MusicFileInfo::getGenre( ) const {
	return genre;
}
const QString & MusicFileInfo::getDate( ) const {
	return date;
}
const QString & MusicFileInfo::getTrack( ) const {
	return track;
}
const QString & MusicFileInfo::getComment( ) const {
	return comment;
}
const QString & MusicFileInfo::getAvcodecGetName( ) const {
	return avcodecGetName;
}
int MusicFileInfo::getSampleRate( ) const {
	return sampleRate;
}
int MusicFileInfo::getNbChannels( ) const {
	return nbChannels;
}
const QString & MusicFileInfo::getAvGetSampleFmtName( ) const {
	return avGetSampleFmtName;
}
int64_t MusicFileInfo::getBitRate( ) const {
	return bitRate;
}
int64_t MusicFileInfo::getDurationMillsecond( ) const {
	return durationMillsecond;
}
const QString & MusicFileInfo::getDurationMillsecondDateTimeString( ) const {
	return durationMillsecondDateTimeString;
}
const QString & MusicFileInfo::getChannelLayoutDescribe( ) const {
	return channelLayoutDescribe;
}
QStringList MusicFileInfo::toQStringList( ) const {
	#define append_conver_string_var_beg( _append_var_target ) \
		QString( "class %1 {\n" ).arg( TemplateArgs::getTypeName( _append_var_target ) )

	#define append_conver_string_var( _append_var_target ) \
		QString("\t%1 := %2 ;\n").arg( #_append_var_target ).arg( _append_var_target )

	#define append_conver_string_var_end( _append_var_target ) \
		QString("\t%1 := %2 ;\n").arg( #_append_var_target ).arg( _append_var_target )

	#define append_result_var_beg( _append_result_target, _append_var_target ) \
		_append_result_target.append( append_conver_string_var_beg(_append_var_target) )

	#define append_result_var( _append_result_target, _append_var_target ) \
		_append_result_target.append( append_conver_string_var(_append_var_target) )

	#define append_result_var_end( _append_result_target, _append_var_target ) \
		(_append_result_target.append( append_conver_string_var_end(_append_var_target) ), _append_result_target.append( "};") )

	QStringList result;
	append_result_var_beg( result, this );
	append_result_var( result, filePath );
	append_result_var( result, title );
	append_result_var( result, artist );
	append_result_var( result, album );
	append_result_var( result, albumArtist );
	append_result_var( result, genre );
	append_result_var( result, date );
	append_result_var( result, track );
	append_result_var( result, comment );
	append_result_var( result, avcodecGetName );
	append_result_var( result, sampleRate );
	append_result_var( result, nbChannels );
	append_result_var( result, avGetSampleFmtName );
	append_result_var( result, bitRate );
	append_result_var( result, durationMillsecond );
	append_result_var( result, durationMillsecondDateTimeString );
	append_result_var_end( result, channelLayoutDescribe );
	return result;
}
MusicFileInfo::operator QString( ) const {
	return toQStringList( ).join( "" );
}
bool getAudioInfo( QString &result, AVDictionary *meta, const char *key ) {
	if( !meta )
		return false;
	AVDictionaryEntry *entry = av_dict_get( meta, key, nullptr, AV_DICT_IGNORE_SUFFIX );
	if( entry == nullptr || entry->value == nullptr )
		return false;
	result = QString( entry->value );
	return true;
}
