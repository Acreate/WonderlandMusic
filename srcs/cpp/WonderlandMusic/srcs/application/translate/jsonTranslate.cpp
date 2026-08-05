#include "jsonTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( Json );

bool JsonTranslate::init( ) {
	fileConverJsonDocError = QObject::tr( "文件转 QJsonDocument 对象错误" );
	notFindJsonKey = QObject::tr( "找不到匹配的关键字" );

	return true;
}

const QString & JsonTranslate::getFileConverJsonDocError( ) const {
	return fileConverJsonDocError;
}

const QString & JsonTranslate::getNotFindJsonKey( ) const {
	return notFindJsonKey;
}
