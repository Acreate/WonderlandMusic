#include "userMutex.h"

#include <mutex>
#include <source_location>

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/messageTranslate.h"
#include "../application/translate/userMutexTranslate.h"

#include "../msgInfo/messageErrorOut.h"

#include "../tools/sourceLocationTools.h"

void UserMutex::out_debug_info( ) const {
	QString source_file;
	QString source_function;
	QString source_line;
	MessageTranslate *messageTranslate = nullptr;
	UserMutexTranslate *userMutexTranslate = nullptr;
	auto appInstance = AppInstance::getAppInstance( );
	if( appInstance ) {
		auto appDataManage = appInstance->getAppDataManage( );
		if( appDataManage ) {
			auto appTranslate = appDataManage->getTranslate( );
			if( appTranslate ) {
				messageTranslate = appTranslate->getMessage( );

				userMutexTranslate = appTranslate->getUserMutex( );
			}
		}
	}

	if( messageTranslate == nullptr ) {
		messageTranslate = new MessageTranslate;
		if( messageTranslate->init( ) ) {
			source_file = messageTranslate->getSourceFile( );
			source_function = messageTranslate->getSourceFunction( );
			source_line = messageTranslate->getSourceLine( );
		} else {
			source_file = QObject::tr( "源文件" );
			source_function = QObject::tr( "源函数" );
			source_line = QObject::tr( "源行号" );
		}
		delete messageTranslate;
	} else {
		source_file = messageTranslate->getSourceFile( );
		source_function = messageTranslate->getSourceFunction( );
		source_line = messageTranslate->getSourceLine( );
	}
	QString trylockError;
	QString lastTrylock;
	QString lastLock;
	QString lastUnlock;
	if( userMutexTranslate == nullptr ) {
		userMutexTranslate = new UserMutexTranslate;
		if( userMutexTranslate->init( ) ) {
			trylockError = userMutexTranslate->getTrylockError( );
			lastTrylock = userMutexTranslate->getLastTrylock( );
			lastLock = userMutexTranslate->getLastLock( );
			lastUnlock = userMutexTranslate->getLastUnlock( );
		} else {
			trylockError = QObject::tr( "锁异常" );
			lastTrylock = QObject::tr( "最后一次尝试锁" );
			lastUnlock = QObject::tr( "最后一次解锁" );
			lastLock = QObject::tr( "最后一次锁" );
		}
		delete userMutexTranslate;
	} else {
		trylockError = userMutexTranslate->getTrylockError( );
		lastTrylock = userMutexTranslate->getLastTrylock( );
		lastLock = userMutexTranslate->getLastLock( );
		lastUnlock = userMutexTranslate->getLastUnlock( );
	}

	MessageString messageString;

	messageString << trylockError << " || " << "\n\t" << lastTrylock << "\t->";
	QString file;
	QString line;
	QString fun;
	SourceLocationTools::formatSourceFilePath( file, fun, line, *trylockSourceLocation );
	if( file.isEmpty( ) == false )
		messageString << "\n\t\t" << source_file << " : " << file;
	if( fun.isEmpty( ) == false )
		messageString << "\n\t\t" << source_function << " : " << fun;
	if( line.isEmpty( ) == false )
		messageString << "\n\t\t" << source_line << " : " << line;
	messageString << "\n\t" << lastLock << "\t->";
	SourceLocationTools::formatSourceFilePath( file, fun, line, *lockSourceLocation );

	if( file.isEmpty( ) == false )
		messageString << "\n\t\t" << source_file << " : " << file;
	if( fun.isEmpty( ) == false )
		messageString << "\n\t\t" << source_function << " : " << fun;
	if( line.isEmpty( ) == false )
		messageString << "\n\t\t" << source_line << " : " << line;
	messageString << "\n\t" << lastUnlock << "\t->";
	SourceLocationTools::formatSourceFilePath( file, fun, line, *unlockSourceLocation );

	if( file.isEmpty( ) == false )
		messageString << "\n\t\t" << source_file << " : " << file;
	if( fun.isEmpty( ) == false )
		messageString << "\n\t\t" << source_function << " : " << fun;
	if( line.isEmpty( ) == false )
		messageString << "\n\t\t" << source_line << " : " << line;
	Message_Error_Out << messageString;
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
		_STD _Throw_Cpp_error( std::_RESOURCE_DEADLOCK_WOULD_OCCUR );
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
		_STD _Throw_Cpp_error( std::_RESOURCE_DEADLOCK_WOULD_OCCUR );
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
		_STD _Throw_Cpp_error( std::_RESOURCE_DEADLOCK_WOULD_OCCUR );
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
