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
	static Create_Ptr_Type * make_args_ptr( Create_Ptr_Type *&ptr, ptr_create_function_args && ...args ) {
		ptr = new Create_Ptr_Type( std::forward< ptr_create_function_args >( args ) ... );
		return ptr;
	}


}

#endif // TEMPLATEARGS_H_H_HEAD__FILE__
