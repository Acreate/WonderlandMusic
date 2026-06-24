#include "musicPlayerThread.h"
#include <QFutureWatcher>
#include <QtConcurrent>

MusicPlayerThread::MusicPlayerThread( const QString &music_file_path ) : musicFilePath( music_file_path ) {
	controlGepTime = 100;
	isJump = true;
}

MusicPlayerThread::~MusicPlayerThread( ) {
}

bool MusicPlayerThread::startPlayerMusic( ) {
	if( this == nullptr )
		return false;

	QFutureWatcher< void > *watcher = new QFutureWatcher< void >( this );
	if( watcher == nullptr )
		return false;

	QFuture< void > future = QtConcurrent::run( [this]( ) {
		playerThread( this );
	} );
	if( future.isValid( ) == false ) {
		watcher->deleteLater( );
		return false;
	}
	connect( watcher, &QFutureWatcher< void >::finished, this, [=]( ) {
		emit threadOver( );
		watcher->deleteLater( );
	} );

	watcher->setFuture( future );
	return true;
}

unsigned long MusicPlayerThread::getControlGepTime( ) const {
	return controlGepTime;
}

void MusicPlayerThread::setControlGepTime( const unsigned long control_gep_time ) {
	controlGepTime = control_gep_time;
}
