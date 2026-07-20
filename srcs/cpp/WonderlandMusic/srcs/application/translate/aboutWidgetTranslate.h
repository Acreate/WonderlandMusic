#ifndef ABOUTWIDGETTRANSLATE_H_H_HEAD__FILE__
#define ABOUTWIDGETTRANSLATE_H_H_HEAD__FILE__
#include <interface/iTranslate.h>

class AboutWidgetTranslate : public ITranslate {
	QString titleName;

public:
	bool init( ) override;

	virtual const QString & getTitleName( ) const;
};
#endif // ABOUTWIDGETTRANSLATE_H_H_HEAD__FILE__
