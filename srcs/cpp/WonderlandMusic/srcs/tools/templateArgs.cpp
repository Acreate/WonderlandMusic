#include "templateArgs.h"

#include "../interface/iAppCore.h"
QString TemplateArgs::getTypeName( nullptr_t ty ) {
	return QString( "void" );
}
QString TemplateArgs::getCaseTypeName( void *ty ) {
	if( ty ) {
		auto casePtr = IAppCore::case_ptr( ty );
		if( casePtr )
			return casePtr->getTypeName( );
	}
	return QString( );
}
QString TemplateArgs::getCaseTypeName( QObject *ty ) {
	return ty->metaObject( )->className( );
}
QString TemplateArgs::getCaseTypeName( const QObject *ty ) {
	return ty->metaObject( )->className( );
}
QString TemplateArgs::getCaseTypeName( const void *ty ) {
	if( ty ) {
		auto casePtr = IAppCore::case_ptr( ty );
		if( casePtr )
			return casePtr->getTypeName( );
	}
	return QString( );
}
