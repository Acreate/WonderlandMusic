#include "templateArgs.h"

#include "../component/optionWindow/interface/optionPanel.h"

static const char * getTypeName( const QObject *ty );
static const char * getTypeName( const IAppCore *ty );

const char * TemplateArgs::getCaseTypeName( const void *ty ) {
	auto casePtr = IAppCore::case_ptr( ty );
	return getTypeName( casePtr );
}
const char * getTypeName( const QObject *ty ) {
	if( ty == nullptr )
		return nullptr;
	return ty->metaObject( )->className( );
}

const char * getTypeName( const IAppCore *ty ) {
	if( ty == nullptr )
		return nullptr;
	auto typeName = ty->getTypeName( );
	if( typeName == nullptr )
		return getTypeName( qobject_cast< QObject * >( ( QObject * ) ty ) );
	return typeName;
}
