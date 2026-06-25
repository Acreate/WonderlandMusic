#include "musicPlayerThread.h"
#include <QtConcurrent>

#include "../application/appInstance.h"

bool MusicPlayerThread::startPlayerTread( ) {
	if( this == nullptr )
		return false;

	auto watcher = new QFutureWatcher< void >( this );
	if( watcher == nullptr )
		return false;

	QFuture< void > future = QtConcurrent::run( [this]( ) {
		playerThread( this );
	} );
	if( future.isValid( ) == false ) {
		watcher->deleteLater( );
		return false;
	}
	connect( watcher, &QFutureWatcher< void >::started, this, [=]( ) {
		emit threadStart( );
	} );
	connect( watcher, &QFutureWatcher< void >::finished, this, [=]( ) {
		watcher->deleteLater( );
		emit threadOver( );
	} );
	watcher->setFuture( future );
	return true;
}

MusicPlayerThread::MusicPlayerThread( const QString &music_file_path ) : musicFilePath( music_file_path ) {
	controlGepTime = 100;
	isJump = true;
	connect( this, &MusicPlayerThread::startPlayerMusic, [this]( ) {
		startPlayerTread( );
	} );
	connect( this, &MusicPlayerThread::stopPlayerMusic, this, [=]( ) {
		isJump = true;
	} );
}

MusicPlayerThread::~MusicPlayerThread( ) {
}

unsigned long MusicPlayerThread::getControlGepTime( ) const {
	return controlGepTime;
}

void MusicPlayerThread::setControlGepTime( const unsigned long control_gep_time ) {
	controlGepTime = control_gep_time;
}
