#ifndef ITRANSLATE_H_H_HEAD__FILE__
#define ITRANSLATE_H_H_HEAD__FILE__

#include <qstring.h>

class ITranslate {
public:
	ITranslate( ) {
	}

	virtual ~ITranslate( ) {
	}

	virtual bool init( ) = 0;
};

#endif // ITRANSLATE_H_H_HEAD__FILE__
