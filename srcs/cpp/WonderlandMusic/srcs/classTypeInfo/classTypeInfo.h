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
	const void *ptr = nullptr;

protected:
	virtual bool unsafeIsType( const void *&&ptr ) const;
	virtual bool unsafeIsType( const void *&ptr ) const;
	virtual bool unsafeIsType( const type_info &type_info ) const;
	virtual bool unsafeIsType( const QString &type_name ) const;
	virtual bool unsafeGetClassTypeName( const void *&ptr, QString &result_name ) const;
	virtual bool unsafeGetClassTypeName( const void *&&ptr, QString &result_name ) const;

public:
	explicit ClassTypeInfo( const void *ptr, const type_info &type_info, const QString &name );
	virtual ~ClassTypeInfo( );

public:
	virtual bool getClassTypeName( const void *&ptr, QString &result_name ) const;
	virtual bool getClassTypeName( const void *&&ptr, QString &result_name ) const;
	virtual bool isClassType( const void *&&ptr ) const;
	virtual bool isClassType( const void *&ptr ) const;
	virtual bool isClassType( const type_info &type_info ) const;
	virtual bool isClassType( const QString &type_name ) const;
	virtual ClassTypeInfo * appendClassTypeInfo( const void *ptr, const type_info &type_info, const QString &name );
};

#endif // CLASSTYPEINFO_H_H_HEAD__FILE__
