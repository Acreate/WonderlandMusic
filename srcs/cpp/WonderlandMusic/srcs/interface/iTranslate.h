#ifndef ITRANSLATE_H_H_HEAD__FILE__
#define ITRANSLATE_H_H_HEAD__FILE__
#include <head/declaration_get_translate.h>
#include "iAppCore.h"
#include "iAppResourceCore.h"

namespace AppTranslateTools {
}

class ITranslate : public IAppCore , public IAppResourceCore {
protected:
	bool deleteResource( ) override;
	~ITranslate( ) override;

public:
	bool initBefore( ) override;

	bool initAfter( ) override;
};

#endif // ITRANSLATE_H_H_HEAD__FILE__
