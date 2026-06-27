#ifndef USERMUTEX_H_H_HEAD__FILE__
#define USERMUTEX_H_H_HEAD__FILE__
#include <memory>
#include <source_location>

class MessageErrorOut;

namespace std {
	struct source_location;
	class mutex;
}

class UserMutex {
	std::mutex *mutexCorPtr;
	std::source_location *lockSourceLocation;
	std::source_location *trylockSourceLocation;
	std::source_location *unlockSourceLocation;

public:
	UserMutex( );

	UserMutex( const UserMutex &other ) = delete;

	UserMutex & operator=( const UserMutex &other ) = delete;

	virtual bool tryLock( const std::source_location &source_location = std::source_location::current( ) ) const;

	virtual bool lock( const std::source_location &source_location = std::source_location::current( ) ) const;

	virtual bool unlock( const std::source_location &source_location = std::source_location::current( ) ) const;
	virtual std::mutex& getMutex() const;
	virtual ~UserMutex( );
};

#endif // USERMUTEX_H_H_HEAD__FILE__
