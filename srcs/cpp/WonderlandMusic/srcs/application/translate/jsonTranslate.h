#ifndef JSONTRANSLATE_H_H_HEAD__FILE__
#define JSONTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class JsonTranslate : public ITranslate {
	QString fileConverJsonDocError;
	QString notFindJsonKey;

public:
	bool init( ) override;

public:
	virtual const QString & getFileConverJsonDocError( ) const;

	virtual const QString & getNotFindJsonKey( ) const;
};

#endif // JSONTRANSLATE_H_H_HEAD__FILE__
