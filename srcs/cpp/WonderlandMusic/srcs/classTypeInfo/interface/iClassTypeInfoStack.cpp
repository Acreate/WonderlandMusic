#include "iClassTypeInfoStack.h"
#include "iClassTypeInfo.h"
IClassTypeInfoStack::IClassTypeInfoStack( ) {
}
IClassTypeInfoStack::~IClassTypeInfoStack( ) {
}
bool IClassTypeInfoStack::deleteIClassTypeInfo( IClassTypeInfo *&class_type_info ) const {
	if( class_type_info == nullptr )
		return false;
	delete class_type_info;
	class_type_info = nullptr;
	return true;
}
