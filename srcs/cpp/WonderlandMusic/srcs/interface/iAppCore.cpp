#include "iAppCore.h"

#include "../mutex/userMutex.h"

static std::vector< IAppCore * > ptrVector;
static std::shared_ptr< UserMutex > userMutex( new UserMutex );

void IAppCore::appendPtr( IAppCore *ptr ) {
	userMutex->lock( );
	ptrVector.emplace_back( ptr );
	userMutex->unlock( );
}
void IAppCore::removePtr( IAppCore *ptr ) {
	userMutex->lock( );
	size_t count = ptrVector.size( );
	if( count ) {
		auto data = ptrVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ] == ptr ) {
				ptrVector.erase( ptrVector.begin( ) + index );
				break;
			}
	}
	userMutex->unlock( );
}
IAppCore * IAppCore::case_ptr( void *ptr ) {
	IAppCore *result = nullptr;
	userMutex->lock( );
	size_t count = ptrVector.size( );
	if( count ) {
		auto data = ptrVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ] == ptr ) {
				result = data[ index ];
				break;
			}
	}
	userMutex->unlock( );
	return result;
}
const IAppCore * IAppCore::case_ptr( const void *ptr ) {
	const IAppCore *result = nullptr;
	userMutex->lock( );
	size_t count = ptrVector.size( );
	if( count ) {
		auto data = ptrVector.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ] == ptr ) {
				result = data[ index ];
				break;
			}
	}
	userMutex->unlock( );
	return result;
}
IAppCore::IAppCore( ) {
	appendPtr( this );
}
IAppCore::~IAppCore( ) {
	removePtr( this );
}
QString IAppCore::getTypeName( ) const {
	return nullptr;
}
