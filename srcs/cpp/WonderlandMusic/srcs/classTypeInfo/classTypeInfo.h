#ifndef CLASSTYPEINFO_H_H_HEAD__FILE__
#define CLASSTYPEINFO_H_H_HEAD__FILE__

#include <vector>

class UserMutex;
class QString;

class ClassTypeInfo {
protected:
	UserMutex *userMutex;
	QString *name;
	const type_info &typeInfo;
	std::vector< ClassTypeInfo * > aliasTypeInfos;

protected:
	virtual bool unsafeIsType( const type_info &type_info ) const;
	virtual bool unsafeIsType( const QString &type_name ) const;

public:
	explicit ClassTypeInfo( const type_info &type_info );
	explicit ClassTypeInfo( const type_info &type_info, const QString &name );
	virtual ~ClassTypeInfo( );
	virtual bool isClassType( const type_info &type_info ) const;
	virtual bool isClassType( const QString &type_name ) const;
	virtual ClassTypeInfo * appendClassTypeInfo( const type_info &type_info, const QString &name );
	virtual ClassTypeInfo * appendClassTypeInfo( const type_info &type_info );
};
#endif // CLASSTYPEINFO_H_H_HEAD__FILE__
