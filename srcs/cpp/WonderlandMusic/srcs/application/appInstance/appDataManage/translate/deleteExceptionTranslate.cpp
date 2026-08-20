#include "deleteExceptionTranslate.h"

bool DeleteExceptionTranslate::init( ) {
	deletePtrError = QObject::tr( "无法释放" );
	return true;
}

const QString & DeleteExceptionTranslate::getDeletePtrError( ) const {
	return deletePtrError;
}
