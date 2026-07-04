#ifndef IJSONKEY_H_H_HEAD__FILE__
#define IJSONKEY_H_H_HEAD__FILE__

#include "iAppCore.h"

class IJsonKey : public IAppCore {
protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;

	bool initAfter( ) override;
};

#endif // IJSONKEY_H_H_HEAD__FILE__
