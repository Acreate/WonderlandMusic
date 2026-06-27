#include "userMutex.h"

#include <mutex>
#include <source_location>

UserMutex::UserMutex( ) {
	mutexCorPtr = new std::mutex;
	trylockSourceLocation = new std::source_location;
	lockSourceLocation = new std::source_location;
	unlockSourceLocation = new std::source_location;
}

bool UserMutex::tryLock( const std::source_location &source_location ) const {
	if( mutexCorPtr == nullptr )
		return false;
	bool tryLock = mutexCorPtr->try_lock( );
	*trylockSourceLocation = source_location;
	return tryLock;
}

bool UserMutex::lock( const std::source_location &source_location ) const {
	if( mutexCorPtr == nullptr )
		return false;
	mutexCorPtr->lock( );
	*lockSourceLocation = source_location;
	return true;
}

bool UserMutex::unlock( const std::source_location &source_location ) const {
	if( mutexCorPtr == nullptr )
		return false;
	mutexCorPtr->unlock( );
	*unlockSourceLocation = source_location;
	return true;
}

std::mutex & UserMutex::getMutex( ) const {
	return *mutexCorPtr;
}

UserMutex::~UserMutex( ) {
	if( mutexCorPtr->try_lock( ) == false )
		mutexCorPtr->unlock( );
	delete mutexCorPtr;
	delete trylockSourceLocation;
	delete lockSourceLocation;
	delete unlockSourceLocation;
}
