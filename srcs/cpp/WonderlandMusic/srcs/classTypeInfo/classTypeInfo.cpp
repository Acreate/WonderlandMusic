#include "classTypeInfo.h"

#include <QString>

#include "../mutex/userMutex.h"
bool ClassTypeInfo::unsafeIsType( const void *&&ptr ) const {
	if( ptr == this->ptr )
		return true;
	size_t count = aliasTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = aliasTypeInfos.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ]->unsafeIsType( ptr ) )
			return true;
	return false;
}
bool ClassTypeInfo::unsafeIsType( const void *&ptr ) const {
	if( ptr == this->ptr )
		return true;
	size_t count = aliasTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = aliasTypeInfos.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ]->unsafeIsType( ptr ) )
			return true;
	return false;
}
bool ClassTypeInfo::unsafeIsType( const type_info &type_info ) const {
	if( typeInfo == type_info )
		return true;
	auto name = type_info.name( );
	if( name == typeInfo.name( ) )
		return true;
	if( name == *this->name )
		return true;
	size_t count = aliasTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = aliasTypeInfos.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ]->unsafeIsType( type_info ) )
			return true;
	return false;
}
bool ClassTypeInfo::unsafeIsType( const QString &type_name ) const {
	if( typeInfo.name( ) == type_name )
		return true;
	if( type_name == *this->name )
		return true;
	size_t count = aliasTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = aliasTypeInfos.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( data[ index ]->unsafeIsType( type_name ) )
			return true;
	return false;
}
bool ClassTypeInfo::unsafeGetClassTypeName( const void *&ptr, QString &result_name ) const {
	size_t count = aliasTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = aliasTypeInfos.data( );
	size_t index = count;
	do
		if( index -= 1, data[ index ]->ptr == ptr ) {
			result_name = *data[ index ]->name;
			return true;
		}
	while( index != 0 );
	index = count;
	do
		if( index -= 1, data[ index ]->unsafeGetClassTypeName( ptr, result_name ) ) {
			result_name = *data[ index ]->name;
			return true;
		}
	while( index != 0 );
	if( this == ptr ) {
		result_name = *name;
		return true;
	}
	return false;
}
bool ClassTypeInfo::unsafeGetClassTypeName( const void *&&ptr, QString &result_name ) const {
	size_t count = aliasTypeInfos.size( );
	if( count == 0 )
		return false;
	auto data = aliasTypeInfos.data( );
	size_t index = count;
	do
		if( index -= 1, data[ index ]->ptr == ptr ) {
			result_name = *data[ index ]->name;
			return true;
		}
	while( index != 0 );
	index = count;
	do
		if( index -= 1, data[ index ]->unsafeGetClassTypeName( ptr, result_name ) ) {
			result_name = *data[ index ]->name;
			return true;
		}
	while( index != 0 );
	if( this == ptr ) {
		result_name = *name;
		return true;
	}
	return false;
}
ClassTypeInfo::ClassTypeInfo( void *ptr, const type_info &type_info ) : ClassTypeInfo( ptr, type_info, type_info.name( ) ) {
}
ClassTypeInfo::ClassTypeInfo( void *ptr, const type_info &type_info, const QString &name ) : typeInfo( type_info ), name( new QString( name ) ), ptr( ptr ) {
	userMutex = new UserMutex;
}
ClassTypeInfo::~ClassTypeInfo( ) {
	userMutex->lock( );
	size_t count = aliasTypeInfos.size( );
	if( count ) {
		auto data = aliasTypeInfos.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			delete data[ index ];
		aliasTypeInfos.clear( );
	}
	delete name;
	name = nullptr;
	userMutex->unlock( );
	delete userMutex;
	userMutex = nullptr;
}
bool ClassTypeInfo::getClassTypeName( const void *&ptr, QString &result_name ) const {
	userMutex->lock( );
	auto result = unsafeGetClassTypeName( ptr, result_name );
	userMutex->unlock( );
	return result;
}
bool ClassTypeInfo::getClassTypeName( const void *&&ptr, QString &result_name ) const {
	if( ptr == nullptr )
		return false;
	userMutex->lock( );
	auto result = unsafeGetClassTypeName( ptr, result_name );
	userMutex->unlock( );
	return result;
}
bool ClassTypeInfo::isClassType( const void *&&ptr ) const {
	if( ptr == nullptr )
		return false;
	userMutex->lock( );
	auto result = unsafeIsType( ptr );
	userMutex->unlock( );
	return result;
}
bool ClassTypeInfo::isClassType( const void *&ptr ) const {
	userMutex->lock( );
	auto result = unsafeIsType( ptr );
	userMutex->unlock( );
	return result;
}
bool ClassTypeInfo::isClassType( const type_info &type_info ) const {
	userMutex->lock( );
	auto result = unsafeIsType( type_info );
	userMutex->unlock( );
	return result;
}
bool ClassTypeInfo::isClassType( const QString &type_name ) const {
	userMutex->lock( );
	auto result = unsafeIsType( type_name );
	userMutex->unlock( );
	return result;
}
ClassTypeInfo * ClassTypeInfo::appendClassTypeInfo( void *ptr, const type_info &type_info, const QString &name ) {
	ClassTypeInfo *typeInfo = nullptr;
	userMutex->lock( );
	auto result = unsafeIsType( type_info );
	if( result == false ) {
		typeInfo = new ClassTypeInfo( ptr, type_info, name );
		aliasTypeInfos.emplace_back( typeInfo );
	}
	userMutex->unlock( );
	return typeInfo;
}
ClassTypeInfo * ClassTypeInfo::appendClassTypeInfo( void *ptr, const type_info &type_info ) {
	ClassTypeInfo *typeInfo = nullptr;
	userMutex->lock( );
	auto result = unsafeIsType( type_info );
	if( result == false ) {
		typeInfo = new ClassTypeInfo( ptr, type_info );
		aliasTypeInfos.emplace_back( typeInfo );
	}
	userMutex->unlock( );
	return typeInfo;
}
