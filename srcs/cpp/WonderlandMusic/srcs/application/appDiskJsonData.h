#ifndef APPDISKJSONDATA_H_H_HEAD__FILE__
#define APPDISKJSONDATA_H_H_HEAD__FILE__
#include "appJsonData.h"

class AppDiskJsonData : public AppJsonData {
protected:
	virtual bool readJsonData( ) = 0;

	virtual bool writeJsonData( ) = 0;

public:
};

#endif // APPDISKJSONDATA_H_H_HEAD__FILE__
