#include "deleteExceptionTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( DeleteException );

bool DeleteExceptionTranslate::init( ) {
	deletePtrError = QObject::tr( "无法释放" );
	return true;
}

const QString & DeleteExceptionTranslate::getDeletePtrError( ) const {
	return deletePtrError;
}
