#ifndef ITRANSLATE_H_H_HEAD__FILE__
#define ITRANSLATE_H_H_HEAD__FILE__

#include "iAppCore.h"


class ITranslate : public IAppCore {
protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;

	bool initAfter( ) override;
};

#endif // ITRANSLATE_H_H_HEAD__FILE__
