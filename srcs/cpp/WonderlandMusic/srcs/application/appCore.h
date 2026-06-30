#ifndef APPCORE_H_H_HEAD__FILE__
#define APPCORE_H_H_HEAD__FILE__

#define Init_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr || ptr->init() == false ) return false
#define Delete_Resource_App_Core_Ptr( ptr ) if( ptr ) ( delete ptr, ptr = nullptr )

class AppCore {
protected:
	virtual bool deleteResource( ) = 0;

public:
	virtual ~AppCore( ) = default;

	virtual bool init( ) = 0;
};

#endif // APPCORE_H_H_HEAD__FILE__
