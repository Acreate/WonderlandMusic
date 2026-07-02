#ifndef ARRAYTOOLS_H_H_HEAD__FILE__
#define ARRAYTOOLS_H_H_HEAD__FILE__
#include <functional>

namespace ArrayTools {
	/// @brief 在数组当中查找匹配的元素
	/// @tparam Array_Unity_Type_ 数组元素类型
	/// @param start_index 开始下标，成功则返回匹配下标
	/// @param array_ptr 查找的源数组
	/// @param array_count 查找的源数组个数
	/// @param find_target 查找的目标
	/// @return 不存在返回 false
	template< typename Array_Unity_Type_ >
	bool find( size_t &start_index, const Array_Unity_Type_ *array_ptr, const size_t &array_count, const Array_Unity_Type_ &find_target ) {
		for( ; start_index < array_count; start_index += 1 )
			if( array_ptr[ start_index ] == find_target )
				return true;
		return false;
	}

	/// @brief 在数组当中查找匹配的元素
	/// @tparam Array_Unity_Type_ 数组元素类型
	/// @param start_index 开始下标，成功则返回匹配下标
	/// @param array_ptr 查找的源数组
	/// @param array_count 查找的源数组个数
	/// @param comp_function 查找的目标时调用的函数对象
	/// @return 不存在返回 false
	template< typename Array_Unity_Type_ >
	bool find( size_t &start_index, const Array_Unity_Type_ *array_ptr, const size_t &array_count, const std::function< bool( const Array_Unity_Type_ & ) > &comp_function ) {
		for( ; start_index < array_count; start_index += 1 )
			if( comp_function.comp( array_ptr[ start_index ] ) )
				return true;
		return false;
	}
};

#endif // ARRAYTOOLS_H_H_HEAD__FILE__
