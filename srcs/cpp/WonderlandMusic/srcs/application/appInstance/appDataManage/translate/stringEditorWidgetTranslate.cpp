#include "stringEditorWidgetTranslate.h"
bool StringEditorWidgetTranslate::init( ) {
	okString = QObject::tr( "确定" );
	cancelString = QObject::tr( "取消" );
	hint = QObject::tr( "已经存在" );
	return true;
}
const QString & StringEditorWidgetTranslate::getOkString( ) const {
	return okString;
}
const QString & StringEditorWidgetTranslate::getCancelString( ) const {
	return cancelString;
}
const QString & StringEditorWidgetTranslate::getHint( ) const {
	return hint;
}
