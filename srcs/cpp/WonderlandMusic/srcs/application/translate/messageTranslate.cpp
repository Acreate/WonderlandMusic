#include "messageTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( Message );

bool MessageTranslate::init( ) {
	sourceFile = QObject::tr( "源文件" );
	sourceFunction = QObject::tr( "源函数" );
	sourceLine = QObject::tr( "源行号" );
	createDirError = QObject::tr( "创建目录失败" );
	createFileError = QObject::tr( "创建文件失败" );

	openFileError = QObject::tr( "打开文件失败" );
	readFileError = QObject::tr( "读取文件失败" );
	writeFileError = QObject::tr( "写入文件失败" );
	return true;
}

const QString & MessageTranslate::getSourceFile( ) const {
	return sourceFile;
}

const QString & MessageTranslate::getSourceFunction( ) const {
	return sourceFunction;
}

const QString & MessageTranslate::getSourceLine( ) const {
	return sourceLine;
}

const QString & MessageTranslate::getCreateDirError( ) const {
	return createDirError;
}

const QString & MessageTranslate::getCreateFileError( ) const {
	return createFileError;
}

const QString & MessageTranslate::getOpenFileError( ) const {
	return openFileError;
}

const QString & MessageTranslate::getWriteFileError( ) const {
	return writeFileError;
}

const QString & MessageTranslate::getReadFileError( ) const {
	return readFileError;
}
