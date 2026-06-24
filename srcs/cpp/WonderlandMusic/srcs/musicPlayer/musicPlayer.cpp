#include "musicPlayer.h"

#include <QAudioSink>
#include <QMediaPlayer>
#include <QIODevice>

#include "../application/appInstance.h"

#include "../msgInfo/messageErrorOut.h"

#include "../thread/musicPlayerThread/musicAudioSinkPlayerThread.h"
#include "../thread/musicPlayerThread/musicMediaPlayerThread.h"

#include "../tools/pathTools.h"

#define  d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)

void MusicPlayer::deleteResource( ) {
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

	musicFilePath = loadMusicFileInfo.absoluteFilePath( );
	auto musicPlayerThread = new MusicMediaPlayerThread( musicFilePath );

	connect( musicPlayerThread, &MusicPlayerThread::positionChanged, musicPlayerThread, [] ( qint64 position ) {
	} );
	connect( musicPlayerThread, &MusicPlayerThread::durationChanged, musicPlayerThread, [this, musicPlayerThread] ( qint64 duration ) {
		if( isPlayerMisucFile == false ) {
			musicPlayerThread->stopPlayerMusic( );
			return;
		}
	} );
	connect( musicPlayerThread, &MusicPlayerThread::threadOver, [musicPlayerThread, this]( ) {
		this->disconnect( this, &QObject::destroyed, musicPlayerThread, &MusicPlayerThread::stopPlayerMusic );
		musicPlayerThread->disconnect( );
		musicPlayerThread->deleteLater( );
		isPlayerMisucFile = false;
		isStop = true;
	} );
	connect( this, &QObject::destroyed, musicPlayerThread, &MusicPlayerThread::stopPlayerMusic );
	// 配置当前对象播放状态
	isPlayerMisucFile = true;
	// 开始播放
	musicPlayerThread->startPlayerMusic( );
	isStop = false;

	return true;
}

const QString & MusicPlayer::getMusicFilePath( ) const {
	return musicFilePath;
}

bool MusicPlayer::isIsPlayerMisucFile( ) const {
	return isPlayerMisucFile;
}

bool MusicPlayer::isIsStop( ) const {
	return isStop;
}
