#ifndef IAPPDISKJSONDATA_H_H_HEAD__FILE__
#define IAPPDISKJSONDATA_H_H_HEAD__FILE__
#include "iAppJsonData.h"

class IAppDiskJsonData : public IAppJsonData {
protected:
	~IAppDiskJsonData( ) override;

public:
	virtual bool readJsonData( ) = 0;

	virtual bool writeJsonData( ) = 0;
};

#endif // IAPPDISKJSONDATA_H_H_HEAD__FILE__
