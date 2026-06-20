#ifndef IJSONKEY_H_H_HEAD__FILE__
#define IJSONKEY_H_H_HEAD__FILE__
#include <QString>

class IJsonKey {
public:
	IJsonKey( ) = default;

	virtual ~IJsonKey( ) = default;

	virtual bool init( ) = 0;
};

#endif // IJSONKEY_H_H_HEAD__FILE__
