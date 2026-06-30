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
	friend class Template;

	class Template {
		friend class AppCore;

		template< appCoreType::AppCoreBase Make_Ptr >
		static void * make_app_ptr( Make_Ptr *&make_ptr ) {
			make_ptr = new Make_Ptr;
			return make_ptr;
		}

		template< appCoreType::AppCoreBase Delete_Ptr >
		static void * delete_app_ptr( Delete_Ptr *&delete_ptr ) {
			if( delete_ptr == nullptr )
				return nullptr;
			if( static_cast< AppCore * >( delete_ptr )->deleteResource( ) == false )
				return delete_ptr;
			delete delete_ptr;
			delete_ptr = nullptr;
			return delete_ptr;
		}

		template< appCoreType::AppCoreBase Init_Ptr >
		static void * init_app_ptr( Init_Ptr *&init_ptr ) {
			if( init_ptr->init( ) == false )
				return init_ptr;
			return nullptr;
		}

		template< appCoreType::PtrBase Make_Ptr >
		static void * make_any_ptr( Make_Ptr *&make_ptr ) {
			make_ptr = new Make_Ptr;
			return make_ptr;
		}

		template< appCoreType::PtrBase Delete_Ptr >
		static void * delete_any_ptr( Delete_Ptr *&delete_ptr ) {
			if( delete_ptr == nullptr )
				return nullptr;
			delete delete_ptr;
			delete_ptr = nullptr;
			return delete_ptr;
		}

		template< appCoreType::PtrBase Delete_Ptr >
			requires requires ( Delete_Ptr *ptr, bool &result_bool ) {
				result_bool = ptr->init( );
			}
		static void * init_any_ptr( Delete_Ptr *&init_ptr ) {
			if( init_ptr->init( ) == false )
				return init_ptr;
			return nullptr;
		}
	};

protected:
	template< typename Type >
	static void * make_ptr( Type * &make_ptr_ref ) {
		if constexpr( appCoreType::AppCoreBase< Type > ) {
			if( Template::make_app_ptr( make_ptr_ref ) == nullptr )
				return nullptr;
		} else {
			if( Template::make_any_ptr( make_ptr_ref ) == nullptr )
				return nullptr;
		}
		return make_ptr_ref;
	}

	template< typename Type, typename ...Type_List >
	static void * make_ptr( Type * &make_ptr_ref, Type_List ...make_ptr_ref_list ) {
		if( make_ptr( make_ptr_ref ) == nullptr )
			return nullptr;

		return make_ptr( make_ptr_ref_list ... );
	}

	template< typename Type >
	static void * delete_ptr( Type * &make_ptr_ref ) {
		if constexpr( appCoreType::AppCoreBase< Type > ) {
			if( Template::delete_app_ptr( make_ptr_ref ) )
				return make_ptr_ref;
		} else {
			if( Template::delete_any_ptr( make_ptr_ref ) == nullptr )
				return make_ptr_ref;
		}
		return nullptr;
	}

	template< typename Type, typename ...Type_List >
	static void * delete_ptr( Type * &make_ptr_ref, Type_List ...make_ptr_ref_list ) {
		if( delete_ptr( make_ptr_ref ) )
			return make_ptr_ref;

		return delete_ptr( make_ptr_ref_list ... );
	}

	template< typename Type >
	static void * init_ptr( Type * &make_ptr_ref ) {
		if constexpr( appCoreType::AppCoreBase< Type > ) {
			if( Template::init_app_ptr( make_ptr_ref ) )
				return make_ptr_ref;
		} else {
			if( Template::init_any_ptr( make_ptr_ref ) == nullptr )
				return make_ptr_ref;
		}
		return nullptr;
	}

	template< typename Type, typename ...Type_List >
	static void * init_ptr( Type * &make_ptr_ref, Type_List ...make_ptr_ref_list ) {
		if( init_ptr( make_ptr_ref ) )
			return make_ptr_ref;

		return init_ptr( make_ptr_ref_list ... );
	}

protected:
	virtual bool deleteResource( ) = 0;

public:
	virtual ~AppCore( ) = default;

	virtual bool init( ) = 0;
};

#endif // APPCORE_H_H_HEAD__FILE__
