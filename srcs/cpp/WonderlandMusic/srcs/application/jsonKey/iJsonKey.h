#ifndef IJSONKEY_H_H_HEAD__FILE__
#define IJSONKEY_H_H_HEAD__FILE__
#include <QString>

#include <application/appCore.h>

class IJsonKey : public AppCore {
protected:
	bool deleteResource( ) override;
};

#endif // IJSONKEY_H_H_HEAD__FILE__
