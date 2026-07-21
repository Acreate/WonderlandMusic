#ifndef USERMUTEX_H_H_HEAD__FILE__
#define USERMUTEX_H_H_HEAD__FILE__
#include <memory>
#include <mutex>
#include <source_location>

class UserMutex {
public:
	using LockGuard = std::shared_ptr< std::lock_guard< std::mutex > >;

protected:
	std::mutex *mutexCorPtr;
	std::source_location *lockSourceLocation;
	std::source_location *trylockSourceLocation;
	std::source_location *unlockSourceLocation;

protected:
	virtual void out_debug_info( ) const;

public:
	UserMutex( );
	UserMutex( const UserMutex &other ) = delete;
	UserMutex & operator=( const UserMutex &other ) = delete;
	virtual bool tryLock( const std::source_location &source_location = std::source_location::current( ) ) const;
	virtual bool lock( const std::source_location &source_location = std::source_location::current( ) ) const;
	virtual bool unlock( const std::source_location &source_location = std::source_location::current( ) ) const;
	virtual LockGuard getLockGuard( ) const;
	virtual ~UserMutex( );

protected:
	virtual bool tryLock( std::mutex *mutex_cor_ptr, const std::source_location &source_location = std::source_location::current( ) ) const;
	virtual bool lock( std::mutex *mutex_cor_ptr, const std::source_location &source_location = std::source_location::current( ) ) const;
	virtual bool unlock( std::mutex *mutex_cor_ptr, const std::source_location &source_location = std::source_location::current( ) ) const;
	virtual LockGuard getLockGuard( std::mutex *mutex_cor_ptr ) const;
};
#endif // USERMUTEX_H_H_HEAD__FILE__
