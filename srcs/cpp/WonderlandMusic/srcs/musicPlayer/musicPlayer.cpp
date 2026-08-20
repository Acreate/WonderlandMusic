#include "musicPlayer.h"

#include <QAudioSink>
#include <QMediaPlayer>
#include <QIODevice>

#include "../application/appInstance/applicationManage.h"

#include "../msgInfo/messageErrorOut.h"

#include "../thread/musicPlayerThread/musicMediaPlayerThread.h"

#include "../tools/instanceTools.h"
#include "../tools/pathTools.h"

bool MusicPlayer::deleteResource( ) {
	playerStop( );
	return true;
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
	connect( musicPlayerThread, &MusicPlayerThread::threadOver, this, [this]( ) {
		this->disconnect( this, &QObject::destroyed, musicPlayerThread, &MusicPlayerThread::stopPlayerMusic );
		musicPlayerThread->disconnect( );
		musicPlayerThread->deleteLater( );
		musicPlayerThread = nullptr;
		emit playerOver( );
	} );
	connect( musicPlayerThread, &MusicPlayerThread::threadStart, this, [this]( ) {
		emit playerStart( );
	} );
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
		auto appInstance = InstanceTools::getApplicationManage( );
		while( musicPlayerThread != nullptr )
			appInstance->processEvents( );
	}
	return true;
}

qint64 MusicPlayer::getDuratction( ) const {
	if( musicPlayerThread )
		return 0;
	return musicPlayerThread->getDuratction( );
}
