#ifndef ISELECTDIRWIDGETTRANSLATE_H_H_HEAD__FILE__
#define ISELECTDIRWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class ISelectDirWidgetTranslate : public ITranslate{
	QString pathLineEditorPlaceholderText;
	QString pathSelectButtonText;
public:
	bool init( ) override;

	virtual const QString & getPathLineEditorPlaceholderText( ) const;

	virtual const QString & getPathSelectButtonText( ) const;
};

#endif // ISELECTDIRWIDGETTRANSLATE_H_H_HEAD__FILE__
