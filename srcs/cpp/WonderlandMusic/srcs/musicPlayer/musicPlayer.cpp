#include "musicPlayer.h"

#include <QAudioSink>
#include <QMediaPlayer>
#include <QIODevice>

#include "../application/appDataManage.h"
#include "../application/appEventManage.h"
#include "../application/appInstance.h"

#include "../msgInfo/messageErrorOut.h"

#include "../thread/musicPlayerThread/musicMediaPlayerThread.h"

#include "../tools/pathTools.h"

#define  d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)

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
	AppEventManage::Connect_MusicPlayerThread_Signal( [this] ( AppEventManage *sender_ptr, MusicPlayerThread *event_obj_ptr, const MusicPlayerThreadEventInfo &event_info_ref ) {
		auto eventType = event_info_ref.getEventType( );
		switch( eventType ) {
			case MusicPlayerThreadEventInfo::EventType::Position :
				break;
			case MusicPlayerThreadEventInfo::EventType::Duration :
				break;
			case MusicPlayerThreadEventInfo::EventType::Thread_Over : {
				this->disconnect( this, &QObject::destroyed, musicPlayerThread, &MusicPlayerThread::stopPlayerMusic );
				musicPlayerThread->disconnect( );
				musicPlayerThread->deleteLater( );
				musicPlayerThread = nullptr;
				MusicPlayerEventInfo info;
				info.eventSenderPtr = this;
				info.event = MusicPlayerEventInfo::EventType::Player_Over;
				Emit_MusicPlayer_Event( this, info );
			}
			break;
			case MusicPlayerThreadEventInfo::EventType::Thread_Start : {
				MusicPlayerEventInfo info;
				info.eventSenderPtr = this;
				info.event = MusicPlayerEventInfo::EventType::Player_Start;
				Emit_MusicPlayer_Event( this, info );
			}
			break;
		}
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
		auto appInstance = AppInstance::getAppInstance( );
		while( musicPlayerThread != nullptr )
			appInstance->processEvents( );
	}
	return true;
}
