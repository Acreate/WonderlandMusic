#ifndef IAPPCORE_H_H_HEAD__FILE__
#define IAPPCORE_H_H_HEAD__FILE__

#include <QObject>
class ClassTypeInfo;
class UserMutex;

class IAppCore {
private:
	UserMutex *typeInfoUserMutex = nullptr;
	ClassTypeInfo *classTypeInfo = nullptr;
	static void appendPtr( IAppCore *ptr );
	static void removePtr( IAppCore *ptr );
	ClassTypeInfo * appendClassTypeInfo( void *ptr, const type_info &type_info );
	ClassTypeInfo * appendClassTypeInfo( void *ptr, const type_info &type_info, const QString &type_name );

	bool isClassType( const void *&ptr ) const;
	bool isClassType( const void *&&ptr ) const;
	bool isClassType( const type_info &type_info ) const;

	bool isClassType( const QString &type_name ) const;

public:
	static IAppCore * case_ptr( void *ptr );
	static const IAppCore * case_ptr( const void *ptr );

protected:
	template< typename T >
	ClassTypeInfo * appendTypeInfo( T *ptr ) {
		return appendClassTypeInfo( ptr, typeid( T ) );
	}

public:
	IAppCore( );
	virtual ~IAppCore( );

	/// @brief 获取类名称
	/// @return 类名称
	virtual QString getTypeName( ) const;

	template< typename T >
	bool isType( T *&&ptr ) {
		return isClassType( ptr );
	}
	template< typename T >
	bool isType( T *&ptr ) {
		return isClassType( ptr );
	}
	template< typename T >
	bool isType( ) {
		return isClassType( typeid( T ) );
	}
	bool isType( const QString &type_name ) {
		return isClassType( type_name );
	}
};
#endif // IAPPCORE_H_H_HEAD__FILE__
