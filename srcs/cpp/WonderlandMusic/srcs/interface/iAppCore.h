#ifndef IAPPCORE_H_H_HEAD__FILE__
#define IAPPCORE_H_H_HEAD__FILE__

#include <QString>
#include <QObject>

class IAppCore {
private:
	static void appendPtr( IAppCore *ptr );
	static void removePtr( IAppCore *ptr );

public:
	static IAppCore * case_ptr( void *ptr );
	static const IAppCore * case_ptr( const void *ptr );

protected:
	virtual bool deleteResource( ) = 0;

public:
	IAppCore( );
	virtual ~IAppCore( );

	/// @brief 在初始化之前调用，建议在此调用的成员创建流程
	/// @return 成功返回 true
	virtual bool initBefore( ) = 0;

	/// @brief 初始化，建议在此调用的成员初始化流程
	/// @return 成功返回 true
	virtual bool init( ) = 0;

	/// @brief 初始化之后调用，建议在此调用成员的关联
	/// @return 成功返回 true
	virtual bool initAfter( ) = 0;

	/// @brief 获取类名称
	/// @return 类名称
	virtual QString getTypeName( ) const;
};
#endif // IAPPCORE_H_H_HEAD__FILE__
