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
	playerStop( );
}

MusicPlayer::MusicPlayer( QObject *parent ) : QObject( parent ) {
}

MusicPlayer::~MusicPlayer( ) {
	deleteResource( );
}

bool MusicPlayer::init( ) {
	deleteResource( );
	return true;
}

bool MusicPlayer::playerMusic( const QString &music_file ) {
	QFileInfo loadMusicFileInfo( music_file );
	if( loadMusicFileInfo.exists( ) == false )
		return false;
	playerStop( );

	auto newLoadFile = loadMusicFileInfo.absoluteFilePath( );

	musicPlayerThread = new MusicMediaPlayerThread( newLoadFile );

	connect( musicPlayerThread, &MusicPlayerThread::positionChanged, musicPlayerThread, [] ( qint64 position ) {
	}, Qt::QueuedConnection );
	connect( musicPlayerThread, &MusicPlayerThread::durationChanged, musicPlayerThread, [this] ( qint64 duration ) {
	}, Qt::QueuedConnection );
	connect( musicPlayerThread, &MusicPlayerThread::threadOver, this, [ this, newLoadFile]( ) {
		this->disconnect( this, &QObject::destroyed, musicPlayerThread, &MusicPlayerThread::stopPlayerMusic );
		musicPlayerThread->disconnect( );
		musicPlayerThread->deleteLater( );
		musicPlayerThread = nullptr;
		emit playerOver( newLoadFile );
	}, Qt::QueuedConnection );
	connect( musicPlayerThread, &MusicPlayerThread::threadStart, this, [ this, newLoadFile]( ) {
		emit playerStart( newLoadFile );
	}, Qt::QueuedConnection );
	// 开始播放
	musicPlayerThread->startPlayerMusic( );
	musicFilePath = newLoadFile;
	return true;
}

const QString & MusicPlayer::getMusicFilePath( ) const {
	return musicFilePath;
}

bool MusicPlayer::getIsStop( ) const {
	return musicPlayerThread;
}

bool MusicPlayer::playerStop( ) {
	if( musicPlayerThread ) {
		musicPlayerThread->stopPlayerMusic( );
		auto appInstance = AppInstance::getAppInstance( );
		while( musicPlayerThread != nullptr )
			appInstance->processEvents( );
	}
	return true;
}
