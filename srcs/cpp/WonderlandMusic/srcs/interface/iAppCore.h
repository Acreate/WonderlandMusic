#ifndef IAPPCORE_H_H_HEAD__FILE__
#define IAPPCORE_H_H_HEAD__FILE__

#include <QString>
#include <QObject>

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
