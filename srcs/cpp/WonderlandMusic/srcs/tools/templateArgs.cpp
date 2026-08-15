#include "templateArgs.h"

#include "../interface/iAppCore.h"
const char * TemplateArgs::getCaseTypeName( void *ty ) {
	if( ty == nullptr )
		return nullptr;
	auto casePtr = IAppCore::case_ptr( ty );
	if( casePtr )
		return casePtr->getTypeName( );
	return nullptr;
}
const char * TemplateArgs::getCaseTypeName( const void *ty ) {
	if( ty == nullptr )
		return nullptr;
	auto casePtr = IAppCore::case_ptr( ty );
	if( casePtr )
		return casePtr->getTypeName( );
	return nullptr;
}
