#ifndef STRINGEDITORWIDGETTRANSLATE_H_H_HEAD__FILE__
#define STRINGEDITORWIDGETTRANSLATE_H_H_HEAD__FILE__
#include <interface/iTranslate.h>

class StringEditorWidgetTranslate : public ITranslate {
	QString okString;
	QString cancelString;
	QString hint;

public:
	bool init( ) override;
	virtual const QString & getOkString( ) const;
	virtual const QString & getCancelString( ) const;
	virtual const QString & getHint( ) const;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( StringEditorWidget );
}
#endif // STRINGEDITORWIDGETTRANSLATE_H_H_HEAD__FILE__
