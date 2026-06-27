#include "userMutexTranslate.h"

#include <QObject>

bool UserMutexTranslate::init( ) {
	nodeSetUnlockError = QObject::tr( "未解锁" );
	trylockError = QObject::tr( "锁异常" );
	lastTrylock = QObject::tr( "最后一次尝试解锁" );
	lastUnlock = QObject::tr( "最后一次解锁" );
	lastLock = QObject::tr( "最后一次锁" );
	return true;
}

const QString & UserMutexTranslate::getNodeSetUnlockError( ) const {
	return nodeSetUnlockError;
}

const QString & UserMutexTranslate::getTrylockError( ) const {
	return trylockError;
}

const QString & UserMutexTranslate::getLastTrylock( ) const {
	return lastTrylock;
}

const QString & UserMutexTranslate::getLastLock( ) const {
	return lastLock;
}

const QString & UserMutexTranslate::getLastUnlock( ) const {
	return lastUnlock;
}
