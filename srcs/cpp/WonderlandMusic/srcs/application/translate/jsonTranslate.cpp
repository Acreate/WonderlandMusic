#include "jsonTranslate.h"

#include <QObject>

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
