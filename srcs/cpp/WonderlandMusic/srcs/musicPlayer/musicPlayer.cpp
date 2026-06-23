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

#include "../tools/autoMakePtrTools.h"

#define  d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)

void MusicPlayer::deleteResource( ) {
	d_r( audioSink );
	d_r( musicDecode );
}

MusicPlayer::MusicPlayer( QObject *parent ) : QObject( parent ) {
}

bool MusicPlayer::init( ) {
	deleteResource( );
	musicDecode = new MusicDecode;
	if( musicDecode->init( ) == false )
		return false;
	return true;
}

bool MusicPlayer::playerMusic( const QString &music_file ) {
	QFileInfo loadMusicFileInfo( music_file );
	if( loadMusicFileInfo.exists( ) == false )
		return false;
	musicDecode->setSource( music_file );
	musicDecode->start( );
	return true;
}
