#ifndef TEMPLATEARGS_H_H_HEAD__FILE__
#define TEMPLATEARGS_H_H_HEAD__FILE__
#include <utility>

namespace TemplateArgs {
	/// @brief 创建指针对象
	/// @tparam Create_Ptr_Type 创建类型
	/// @tparam ptr_create_function_args 调用构造函数时填充的参数
	/// @param ptr 成功创建赋予的参数
	/// @param args 构造函数填充参数列表
	/// @return 创建失败则返回 nullptr 指针
	template< typename Create_Ptr_Type, typename ...ptr_create_function_args >
	static Create_Ptr_Type * make_ptr( Create_Ptr_Type *&ptr, ptr_create_function_args && ...args ) {
		ptr = new Create_Ptr_Type( std::forward< ptr_create_function_args >( args ) ... );
		return ptr;
	}

	/// @brief 释放指针对象
	/// @tparam Create_Ptr_Type 释放目标类型
	/// @param ptr 释放目标指针，成功释放会被重复赋予 nullptr
	/// @return 成功返回 true，并且 ptr 置为 nullptr
	template< typename Create_Ptr_Type >
	static bool delete_ptr( Create_Ptr_Type *&ptr ) {
		if( ptr == nullptr )
			return true;
		delete ptr;
		ptr = nullptr;
		return true;
	}
};

#endif // TEMPLATEARGS_H_H_HEAD__FILE__
