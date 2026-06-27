#include "userMutex.h"

#include <mutex>
#include <source_location>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/userMutexTranslate.h"

#include "../msgInfo/messageErrorOut.h"

void UserMutex::out_debug_info( ) const {
	auto appTranslate = AppInstance::getAppInstance( )->getTranslate( );
	auto userMutexTranslate = appTranslate->getUserMutex( );
	Message_Error_Out << userMutexTranslate->getTrylockError( ) << userMutexTranslate->getLastTrylock( ) << *trylockSourceLocation << userMutexTranslate->getLastLock( ) << *lockSourceLocation << userMutexTranslate->getLastUnlock( ) << *unlockSourceLocation;
}

UserMutex::UserMutex( ) {
	mutexCorPtr = new std::mutex;
	trylockSourceLocation = new std::source_location;
	lockSourceLocation = new std::source_location;
	unlockSourceLocation = new std::source_location;
}

bool UserMutex::tryLock( const std::source_location &source_location ) const {
	if( mutexCorPtr == nullptr )
		return false;
	bool tryLock;
	try {
		tryLock = mutexCorPtr->try_lock( );
	} catch( ... ) {
		out_debug_info( );
		tryLock = false;
	}
	*trylockSourceLocation = source_location;
	return tryLock;
}

bool UserMutex::lock( const std::source_location &source_location ) const {
	if( mutexCorPtr == nullptr )
		return false;

	bool tryLock;
	try {
		mutexCorPtr->lock( );
		tryLock = true;
	} catch( ... ) {
		out_debug_info( );
		tryLock = false;
	}
	*lockSourceLocation = source_location;
	return tryLock;
}

bool UserMutex::unlock( const std::source_location &source_location ) const {
	if( mutexCorPtr == nullptr )
		return false;
	bool tryLock;
	try {
		mutexCorPtr->unlock( );
		tryLock = true;
	} catch( ... ) {
		out_debug_info( );
		tryLock = false;
	}
	*unlockSourceLocation = source_location;
	return true;
}

UserMutex::LockGuard UserMutex::getLockGuard( ) const {
	LockGuard lockGuard( new std::lock_guard< std::mutex >( *mutexCorPtr ) );
	return lockGuard;
}

UserMutex::~UserMutex( ) {
	if( mutexCorPtr->try_lock( ) == false )
		mutexCorPtr->unlock( );
	delete mutexCorPtr;
	delete trylockSourceLocation;
	delete lockSourceLocation;
	delete unlockSourceLocation;
}
