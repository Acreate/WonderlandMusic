#include "iSelectDirWidgetTranslate.h"

#include <QObject>

bool ISelectDirWidgetTranslate::init( ) {
	pathLineEditorPlaceholderText = QObject::tr( "软件配置存储路径" );
	pathSelectButtonText = QObject::tr( "选择路径" );
	return true;
}

const QString & ISelectDirWidgetTranslate::getPathLineEditorPlaceholderText( ) const {
	return pathLineEditorPlaceholderText;
}

const QString & ISelectDirWidgetTranslate::getPathSelectButtonText( ) const {
	return pathSelectButtonText;
}
