#include "musicMediaPlayerThread.h"

#include <QAudioDevice>
#include <QAudioOutput>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QMutex>

#include "../../application/appInstance.h"
#include "../../application/applicationManage.h"

bool MusicMediaPlayerThread::startPlayerTread( ) {
	isRunOver = false;
	return playerThread( this );
}

bool MusicMediaPlayerThread::stopPlayerMusic( ) {
	if( mediaPlayer ) {
		mediaPlayer->stop( );
		auto appInstance = AppInstance::getAppInstance( )->getApplicationManage(  );
		while( mediaPlayer->isPlaying( ) )
			appInstance->processEvents( );
		delete mediaPlayer;
		delete audioOutput;
		mediaPlayer = nullptr;
		audioOutput = nullptr;
	}
	isRunOver = true;
	bool stopPlayerMusic = MusicPlayerThread::stopPlayerMusic( );
	emit threadOver( );
	return stopPlayerMusic;
}

MusicMediaPlayerThread::MusicMediaPlayerThread( const QString &load_file_path ) : MusicPlayerThread( load_file_path ) {
	controlGepTime = 100;
}

MusicMediaPlayerThread::~MusicMediaPlayerThread( ) {
}

qint64 MusicMediaPlayerThread::getDuratction( ) const {
	if( mediaPlayer == nullptr )
		return 0;
	return mediaPlayer->duration( );
}

bool MusicMediaPlayerThread::playerThread( MusicPlayerThread *music_player_thread ) {
	emit threadStart( );
	mediaPlayer = new QMediaPlayer;
	audioOutput = new QAudioOutput;
	connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [this] ( QMediaPlayer::MediaStatus status ) {
		switch( status ) {
			case QMediaPlayer::LoadingMedia :
				break;
			case QMediaPlayer::LoadedMedia :
				break;
			case QMediaPlayer::StalledMedia :
				break;
			case QMediaPlayer::BufferingMedia :
				break;
			case QMediaPlayer::BufferedMedia :
				break;
			case QMediaPlayer::NoMedia :
			case QMediaPlayer::EndOfMedia :
			case QMediaPlayer::InvalidMedia :
				delete mediaPlayer;
				delete audioOutput;
				mediaPlayer = nullptr;
				audioOutput = nullptr;
				isRunOver = true;
				emit threadOver( );
				break;
		}
	}, Qt::QueuedConnection );
	audioOutput->setVolume( 1.0 );

	mediaPlayer->setAudioOutput( audioOutput );

	QFileInfo info( musicFilePath );
	if( info.exists( ) == false )
		return false;
	auto absoluteFilePath = info.absoluteFilePath( );
	auto fromLocalFile = QUrl::fromLocalFile( absoluteFilePath );
	mediaPlayer->setSource( fromLocalFile );

	mediaPlayer->play( );
	isJump = false;
	return true;
}
