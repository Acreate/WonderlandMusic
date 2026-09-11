#ifndef CLASSTYPEINFO_H_H_HEAD__FILE__
#define CLASSTYPEINFO_H_H_HEAD__FILE__
#include <typeinfo>

#include "unsafe/unsafeClassTypeInfo.h"
class TypeInfoRef;
class UserMutex;
class QString;

class ClassTypeInfo : public UnsafeClassTypeInfo {
private:
	UserMutex *userMutex;

public:
	explicit ClassTypeInfo( const ClassTypeInfoVar *class_type_info_var );
	~ClassTypeInfo( ) override;
	const ClassTypeInfoVar * getClassTypeInfoVar( ) const override;

	TypeInfoRef * appendClassTypeInfo( const ClassTypeInfoVar *class_type_info_var, const void *ptr, const std::type_info &type_info, const QString &name ) override;
	bool deleteClassTypeInfo( const void *p ) override;
	TypeInfoRef * getfristClassTypeInfo( const void *ptr ) const override;
	TypeInfoRef * getEntityClassTypeInfo( ) const override;
};

#endif // CLASSTYPEINFO_H_H_HEAD__FILE__
