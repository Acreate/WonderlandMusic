#ifndef IAPPCORE_H_H_HEAD__FILE__
#define IAPPCORE_H_H_HEAD__FILE__

#include <QString>
#include <QObject>

#define Init_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr || ptr->init() == false ) return false
#define Delete_Resource_App_Core_Ptr( ptr ) if( ptr ) ( delete ptr, ptr = nullptr )

class IAppCore {
protected:
	virtual bool deleteResource( ) = 0;

public:
	virtual ~IAppCore( ) = default;

	virtual bool init( ) = 0;
};
#endif // IAPPCORE_H_H_HEAD__FILE__
