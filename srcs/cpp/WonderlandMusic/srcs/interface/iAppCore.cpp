#include "iAppCore.h"

#include <classTypeInfo/classTypeInfo.h>

#include <mutex/userMutex.h>

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
ClassTypeInfo * IAppCore::appendClassTypeInfo( void *ptr, const type_info &type_info ) {
	return classTypeInfo->appendClassTypeInfo( ptr, type_info );
}
ClassTypeInfo * IAppCore::appendClassTypeInfo( void *ptr, const type_info &type_info, const QString &type_name ) {
	return classTypeInfo->appendClassTypeInfo( ptr, type_info, type_name );
}
bool IAppCore::isClassType( const void *&ptr ) const {
	return classTypeInfo->isClassType( ptr );
}
bool IAppCore::isClassType( const void *&&ptr ) const {
	return classTypeInfo->isClassType( ptr );
}
bool IAppCore::isClassType( const type_info &type_info ) const {
	return classTypeInfo->isClassType( type_info );
}
bool IAppCore::isClassType( const QString &type_name ) const {
	return classTypeInfo->isClassType( type_name );
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
	typeInfoUserMutex = new UserMutex;
	classTypeInfo = new ClassTypeInfo( this, typeid( IAppCore ) );
	appendPtr( this );
}
IAppCore::~IAppCore( ) {
	delete classTypeInfo;
	delete classTypeInfo;
	removePtr( this );
}
QString IAppCore::getTypeName( ) const {
	return nullptr;
}
