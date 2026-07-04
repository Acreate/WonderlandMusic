#ifndef IAPPCORE_H_H_HEAD__FILE__
#define IAPPCORE_H_H_HEAD__FILE__

#include <QString>
#include <QObject>
/// @brief 调用一个指针对象进行初始化，失败返回 false
/// @param ptr 被调用初始化的指针对象
#define Init_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr || ptr->init() == false ) return false
/// @brief 调用一个指针对象，进行初始化之前操作，失败返回 false
/// @param ptr 被调用的指针对象
#define Before_Init_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr || ptr->initBefore() == false ) return false
/// @brief 调用一个指针对象，进行初始化之后的操作，失败返回 false
/// @param ptr 被调用的指针对象
#define After_Init_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr || ptr->initAfter() == false ) return false
/// @brief 删除一个指针对象，并且该对象赋值为 nullptr
/// @param ptr 删除的指针对象
#define Delete_Resource_App_Core_Ptr( ptr ) if( ptr ) ( delete ptr, ptr = nullptr )

class IAppCore {
protected:
	virtual bool deleteResource( ) = 0;

public:
	virtual ~IAppCore( ) = default;

	/// @brief 在初始化之前调用，建议在此调用的成员创建流程
	/// @return 成功返回 true
	virtual bool initBefore( ) = 0;

	/// @brief 初始化，建议在此调用的成员初始化流程
	/// @return 成功返回 true
	virtual bool init( ) = 0;

	/// @brief 初始化之后调用，建议在此调用成员的关联
	/// @return 成功返回 true
	virtual bool initAfter( ) = 0;
};
#endif // IAPPCORE_H_H_HEAD__FILE__
