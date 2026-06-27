#include "iSelectPathWidgetTranslate.h"

#include <QObject>

bool ISelectPathWidgetTranslate::init( ) {
	lineEditorPlaceholderText = QObject::tr( "软件配置存储路径" );
	selectButtonText = QObject::tr( "选择对话框" );
	selectDirPathText = QObject::tr( "选择目录" );
	selectFilePathText = QObject::tr( "选择文件" );
	return true;
}

const QString & ISelectPathWidgetTranslate::getLineEditorPlaceholderText( ) const {
	return lineEditorPlaceholderText;
}

const QString & ISelectPathWidgetTranslate::getSelectButtonText( ) const {
	return selectButtonText;
}

const QString & ISelectPathWidgetTranslate::getSelectDirPathText( ) const {
	return selectDirPathText;
}

const QString & ISelectPathWidgetTranslate::getSelectFilePathText( ) const {
	return selectFilePathText;
}
