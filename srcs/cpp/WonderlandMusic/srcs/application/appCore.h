#ifndef APPCORE_H_H_HEAD__FILE__
#define APPCORE_H_H_HEAD__FILE__

#include <utility>
#include <QString>

class AppCore;

namespace appCoreType {
	/// T 必须是 AppCore 的公有派生类
	template< typename T >
	concept AppCoreBase = std::is_base_of_v< AppCore, T > && std::is_convertible_v< T *, AppCore * >;
	/// T 必须是 AppCore 的公有派生类
	template< typename T >
	concept PtrBase = std::is_convertible_v< T *, void * >;

	/// T 必须是 QString
	template< typename T >
	concept QStringType = std::same_as< T, QString >;
}

class AppCore {
protected:
	template< appCoreType::QStringType String_Array >
	static void clearQString( String_Array &string_list ) {
		string_list.clear( );
	}

	template< appCoreType::QStringType ...String_Array >
	static void clearQString( String_Array & ...string_list ) {
		clearQString( string_list ... );
	}

	template< appCoreType::PtrBase Make_Unity >
	static bool make_any_ptr( Make_Unity *&make_ptr ) {
		make_ptr = new Make_Unity;
		return make_ptr != nullptr;
	}

	template< appCoreType::PtrBase Make_Unity, appCoreType::PtrBase ...Make_Array >
	static bool make_any_ptr( Make_Unity *&init_ptr, Make_Array *& ...string_list ) {
		if( make_any_ptr( init_ptr ) == false )
			return false;
		return make_any_ptr( string_list ... );
	}

	template< appCoreType::PtrBase Make_Unity >
	static void del_any_ptr( Make_Unity *&make_ptr ) {
		if( make_ptr )
			delete make_ptr;
		make_ptr = nullptr;
	}

	template< appCoreType::PtrBase Make_Unity, appCoreType::PtrBase ... Make_Array >
	static void del_any_ptr( Make_Unity *&init_ptr, Make_Array *& ...string_list ) {
		del_any_ptr( init_ptr );
		del_any_ptr( string_list ... );
	}

	template< appCoreType::AppCoreBase Init_Unity >
	static bool init_app_core_ptr( Init_Unity *init_ptr ) {
		if( init_ptr->init( ) == false )
			return false;
		return true;
	}

	template< appCoreType::AppCoreBase Init_Unity, appCoreType::AppCoreBase ...Init_Array >
	static bool init_app_core_ptr( Init_Unity *init_ptr, Init_Array * ...string_list ) {
		if( init_ptr->init( ) == false )
			return false;
		return init_app_core_ptr( string_list ... );
	}

	template< appCoreType::AppCoreBase Make_Unity >
	static bool make_app_core_ptr( Make_Unity *&make_ptr ) {
		make_ptr = new Make_Unity;
		return make_ptr != nullptr;
	}

	template< appCoreType::AppCoreBase Make_Unity, appCoreType::AppCoreBase ... Make_Array >
	static bool make_app_core_ptr( Make_Unity *&init_ptr, Make_Array *& ...string_list ) {
		if( make_app_core_ptr( init_ptr ) == false )
			return false;
		return make_app_core_ptr( string_list ... );
	}

	template< appCoreType::AppCoreBase Make_Unity >
	static void del_app_core_ptr( Make_Unity *&make_ptr ) {
		if( make_ptr )
			delete make_ptr;
		make_ptr = nullptr;
	}

	template< appCoreType::AppCoreBase Make_Unity, appCoreType::AppCoreBase ... Make_Array >
	static void del_app_core_ptr( Make_Unity *&init_ptr, Make_Array *& ...string_list ) {
		del_app_core_ptr( init_ptr );
		del_app_core_ptr( string_list ... );
	}

protected:
	virtual bool deleteResource( ) = 0;

public:
	virtual ~AppCore( ) = default;

	virtual bool init( ) = 0;
};

#endif // APPCORE_H_H_HEAD__FILE__
