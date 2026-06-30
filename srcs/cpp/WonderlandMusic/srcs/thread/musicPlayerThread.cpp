#include "musicPlayerThread.h"
#include <QtConcurrent>

#include "../application/appEventManage.h"
#include "../application/appInstance.h"

bool MusicPlayerThread::startPlayerTread( ) {
	if( this == nullptr )
		return false;
	auto watcher = new QFutureWatcher< void >( this );
	if( watcher == nullptr )
		return false;

	QFuture< void > future = QtConcurrent::run( [this]( ) {
		isRunOver = false;
		playerThread( this );
	} );
	if( future.isValid( ) == false ) {
		watcher->deleteLater( );
		return false;
	}
	connect( watcher, &QFutureWatcher< void >::started, this, [=]( ) {
		MusicPlayerThreadEventInfo inf;
		inf.eventSenderPtr = this;
		inf.event = MusicPlayerThreadEventInfo::EventType::Thread_Start;
		Emit_MusicPlayerThread_Event( this, inf );
	} );
	connect( watcher, &QFutureWatcher< void >::finished, this, [=]( ) {
		watcher->deleteLater( );

		MusicPlayerThreadEventInfo inf;
		inf.eventSenderPtr = this;
		inf.event = MusicPlayerThreadEventInfo::EventType::Thread_Over;
		Emit_MusicPlayerThread_Event( this, inf );
		isRunOver = true;
	} );
	watcher->setFuture( future );
	return true;
}

MusicPlayerThread::MusicPlayerThread( const QString &music_file_path ) : musicFilePath( music_file_path ) {
	controlGepTime = 100;
	isJump = true;
}

MusicPlayerThread::~MusicPlayerThread( ) {
	stopPlayerMusic( );
	if( isRunOver == false ) {
		auto appInstance = AppInstance::getAppInstance( );
		while( isRunOver == false )
			appInstance->processEvents( );
	}
}

bool MusicPlayerThread::isIsRunOver( ) const {
	return isRunOver;
}

unsigned long MusicPlayerThread::getControlGepTime( ) const {
	return controlGepTime;
}

bool MusicPlayerThread::stopPlayerMusic( ) {
	isJump = true;
	return true;
}

bool MusicPlayerThread::startPlayerMusic( ) {
	while( isRunOver == false )
		QThread::currentThread( )->msleep( 200 );
	startPlayerTread( );
	return true;
}

void MusicPlayerThread::setPlayerMusicPosition( qint64 position ) {
	this->pos = position;
}

void MusicPlayerThread::setPlayerMusicDuration( qint64 duration ) {
	this->duration = duration;
}

void MusicPlayerThread::setControlGepTime( const unsigned long control_gep_time ) {
	controlGepTime = control_gep_time;
}
