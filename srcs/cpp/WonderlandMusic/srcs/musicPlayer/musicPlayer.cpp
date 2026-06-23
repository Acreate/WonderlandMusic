#include "musicPlayer.h"

#include <QAudioSink>
#include <QMediaPlayer>
#include <QIODevice>
#include <QAudioOutput>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QFileInfo>
#include <QAudioDecoder>

#include "musicDecode.h"

#include "../application/appInstance.h"

#include "../msgInfo/messageErrorOut.h"

#include "../thread/musicPlayerThread.h"

#include "../tools/autoMakePtrTools.h"

#define  d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)

void MusicPlayer::deleteResource( ) {
	d_r( musicDecode );
}

void MusicPlayer::playerMusicFrame( MusicPlayerThread *music_player_thread, QAudioSink *audioSink, QIODevice *ioAudioSinkDevice, const QAudioBuffer &audio_buffer ) {
	if( music_player_thread == nullptr )
		return;
	if( isPlayerMisucFile == false ) {
		music_player_thread->stop( );
		return;
	}
	auto constData = audio_buffer.constData< char >( );
	auto byteCount = audio_buffer.byteCount( );
	ioAudioSinkDevice->write( constData, byteCount );
}

void MusicPlayer::overPlayerMusic( MusicPlayerThread *music_player_thread ) {
	isPlayerMisucFile = false;
	isStop = true;
}

MusicPlayer::MusicPlayer( QObject *parent ) : QObject( parent ) {
}

MusicPlayer::~MusicPlayer( ) {
}

bool MusicPlayer::init( ) {
	deleteResource( );
	isPlayerMisucFile = false;
	isStop = true;

	musicDecode = new MusicDecode;
	if( musicDecode->init( ) == false )
		return false;
	connect( musicDecode, &MusicDecode::finished_Signal, [this] ( const std::vector< QAudioBuffer > &audio_buffer_vector ) {
		size_t size = audio_buffer_vector.size( );
		if( size == 0 )
			return;// 不存在帧数据

		// 创建播放线程
		auto musicPlayerThread = new MusicPlayerThread( audio_buffer_vector );

		// 链接线程播放帧信号
		connect( musicPlayerThread, &MusicPlayerThread::playerMusicFrame, this, &MusicPlayer::playerMusicFrame, Qt::QueuedConnection );
		// 链接线程帧播放完毕的信号
		connect( musicPlayerThread, &MusicPlayerThread::overPlayerMusic, this, &MusicPlayer::overPlayerMusic, Qt::QueuedConnection );
		connect( musicPlayerThread, &QThread::finished, musicPlayerThread, &MusicPlayer::deleteLater, Qt::QueuedConnection );

		// 配置当前对象播放状态
		isPlayerMisucFile = true;
		// 开始播放
		musicPlayerThread->start( );
		isStop = false;
	} );
	connect( musicDecode, &MusicDecode::error_Signal, [this] ( MusicDecode::Error error, const QString &error_msg ) {
		if( musicDecode->isDecoding( ) )
			musicDecode->stop( );
	} );
	return true;
}

bool MusicPlayer::playerMusic( const QString &music_file ) {
	QFileInfo loadMusicFileInfo( music_file );
	if( loadMusicFileInfo.exists( ) == false )
		return false;
	
	// 使用 QMediaPlayer 时，没有噪音
	/*QAudioOutput *audioOutput = new QAudioOutput;
	QMediaPlayer *mediaPlayer = new QMediaPlayer;
	mediaPlayer->setSource( QUrl::fromLocalFile( music_file ) );
	audioOutput->setVolume( 1.0 );
	mediaPlayer->setAudioOutput( audioOutput );
	mediaPlayer->play( );*/

	if( isPlayerMisucFile ) {
		isStop = false;
		isPlayerMisucFile = false;
		auto appInstance = AppInstance::getAppInstance( );
		while( isStop == false )
			appInstance->processEvents( );
	}
	if( musicDecode->isDecoding( ) )
		musicDecode->stop( );

	musicDecode->setSource( music_file );

	musicDecode->start( );
	return true;
}
