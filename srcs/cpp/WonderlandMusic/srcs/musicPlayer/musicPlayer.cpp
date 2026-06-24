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

#include "../thread/musicMediaPlayerThread.h"

#include "../tools/pathTools.h"

#define  d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)

void MusicPlayer::deleteResource( ) {
	d_r( musicDecode );
}

MusicPlayer::MusicPlayer( QObject *parent ) : QObject( parent ) {
}

MusicPlayer::~MusicPlayer( ) {
	deleteResource( );
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
		auto wirteFilePath = "./wriet.wav";
		if( PathTools::wirteWavFile( wirteFilePath, audio_buffer_vector ) == false )
			return;// 缓存写入失败
		auto loadUrl = musicDecode->getLoadUrl( );
		auto localFile = loadUrl->toLocalFile( );
		// 创建播放线程
		auto musicPlayerThread = new MusicMediaPlayerThread( localFile );

		connect( musicPlayerThread, &MusicMediaPlayerThread::positionChanged, musicPlayerThread, [] ( qint64 position ) {
		} );
		connect( musicPlayerThread, &MusicMediaPlayerThread::durationChanged, musicPlayerThread, [this, musicPlayerThread] ( qint64 duration ) {
			if( isPlayerMisucFile == false ) {
				musicPlayerThread->stop( );
				return;
			}
		} );
		connect( musicPlayerThread, &MusicMediaPlayerThread::finished, [musicPlayerThread, this]( ) {
			musicPlayerThread->deleteLater( );
			isPlayerMisucFile = false;
			isStop = true;
		} );

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
