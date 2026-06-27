#ifndef ISELECTPATHWIDGETTRANSLATE_H_H_HEAD__FILE__
#define ISELECTPATHWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class ISelectPathWidgetTranslate : public ITranslate {
	QString lineEditorPlaceholderText;
	QString selectButtonText;
	QString selectDirPathText;
	QString selectFilePathText;

public:
	bool init( ) override;

	virtual const QString & getLineEditorPlaceholderText( ) const;

	virtual const QString & getSelectButtonText( ) const;

	virtual const QString & getSelectDirPathText( ) const;

	virtual const QString & getSelectFilePathText( ) const;
};

#endif // ISELECTPATHWIDGETTRANSLATE_H_H_HEAD__FILE__
