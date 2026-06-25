#ifndef VECTORTOOLS_H_H_HEAD__FILE__
#define VECTORTOOLS_H_H_HEAD__FILE__
#include <functional>
#include <vector>

namespace VectorTools {
	/// @brief 相同类型的比较方法
	/// @tparam UintyType_ 序列中的元素类型
	template< typename UintyType_ >
	using compIdenticalTypeFinction = std::function< bool( const UintyType_ &left, const UintyType_ &right ) >;
	/// @brief 查找匹配方法
	/// @tparam UintyType_ 查找序列中的元素类型
	/// @tparam FindType_ 查找的元素类型
	template< typename UintyType_, typename FindType_ >
	using findItemFinction = std::function< bool( const UintyType_ &org, const FindType_ &find ) >;

	/// @brief 查找元素
	/// @tparam UnityType_ 序列元素类型
	/// @param result_index 目标下标
	/// @param find_vector_source 查找源
	/// @param find_var_target 查找目标
	/// @return 不存在返回 false
	template< typename UnityType_ >
	static bool findIndex( size_t &result_index, const std::vector< UnityType_ > &find_vector_source, const UnityType_ &find_var_target ) {
		auto count = find_vector_source.size( );
		if( count == 0 )
			return false;
		auto data = find_vector_source.data( );
		for( ; result_index < count; ++result_index )
			if( data[ result_index ] == find_var_target )
				return true;
		return false;
	}

	/// @brief 查找元素
	/// @tparam UnityType_ 序列元素类型
	/// @param result_index 目标下标
	/// @param find_vector_source 查找源
	/// @param find_var_target 查找目标
	/// @param find_function 查找函数调用
	/// @return 不存在返回 false
	template< typename UnityType_, typename FindType_ >
	static bool findIndex( size_t &result_index, const std::vector< UnityType_ > &find_vector_source, const FindType_ &find_var_target, const findItemFinction< UnityType_, FindType_ > &find_function ) {
		auto count = find_vector_source.size( );
		if( count == 0 )
			return false;
		auto data = find_vector_source.data( );
		for( ; result_index < count; ++result_index )
			if( find_function( data[ result_index ], find_var_target ) )
				return true;
		return false;
	}

	/// @brief 查找重复元素
	/// @tparam UnityType_ 元素类型
	/// @param find_vector_source 查找源
	/// @param single_cace_vector 返回单例列表
	/// @param result_repetion_vector 返回重复列表
	/// @return 重复数量
	template< typename UnityType_ >
	static size_t getRepetition( const std::vector< UnityType_ > &find_vector_source, std::vector< UnityType_ > &single_cace_vector, std::vector< UnityType_ > &result_repetion_vector ) {
		auto count = find_vector_source.size( );
		if( count == 0 )
			return 0;
		auto data = find_vector_source.data( );
		result_repetion_vector.resize( count );
		single_cace_vector.resize( count );
		auto resultSingCaceData = single_cace_vector.data( );
		auto resultRepetionData = result_repetion_vector.data( );
		decltype(count) foreachIndex = 0;
		decltype(count) repetitionIndex;
		decltype(count) singCaceIndex;
		size_t singCaceCount = 0;
		size_t repetitionCount = 0;
		for( ; foreachIndex < count; ++foreachIndex ) {
			auto &unityRef = data[ foreachIndex ];
			for( singCaceIndex = 0; singCaceIndex < singCaceCount; singCaceIndex += 1 )
				if( resultSingCaceData[ singCaceIndex ] == unityRef )
					break;
			if( singCaceIndex == repetitionCount ) { // 单例
				resultSingCaceData[ singCaceCount ] = unityRef;
				singCaceCount += 1;
			} else {
				bool isJump = false;
				for( repetitionIndex = 0; repetitionIndex < repetitionCount; repetitionIndex += 1 )
					if( resultRepetionData[ repetitionIndex ] == unityRef ) {
						isJump = true;
						break;
					}
				if( isJump )
					continue;
				resultSingCaceData[ repetitionCount ] = unityRef;
				repetitionCount += 1;
			}
		}
		result_repetion_vector.resize( repetitionCount );
		single_cace_vector.resize( singCaceCount );
		return repetitionCount;
	}

	/// @brief 查找重复元素
	/// @tparam UnityType_ 元素类型
	/// @param single_cace_vector 返回单例列表
	/// @param result_repetion_vector 返回重复列表
	/// @param find_vector_source 查找源
	/// @param comp_function 比较方法
	/// @return 重复数量
	template< typename UnityType_ >
	static size_t getRepetition( std::vector< UnityType_ > &single_cace_vector, std::vector< UnityType_ > &result_repetion_vector, const std::vector< UnityType_ > &find_vector_source, const compIdenticalTypeFinction< UnityType_ > &comp_function ) {
		auto count = find_vector_source.size( );
		if( count == 0 )
			return 0;
		auto data = find_vector_source.data( );
		result_repetion_vector.resize( count );
		single_cace_vector.resize( count );
		auto resultSingCaceData = single_cace_vector.data( );
		auto resultRepetionData = result_repetion_vector.data( );
		decltype(count) foreachIndex = 0;
		decltype(count) repetitionIndex;
		decltype(count) singCaceIndex;
		size_t singCaceCount = 0;
		size_t repetitionCount = 0;
		for( ; foreachIndex < count; ++foreachIndex ) {
			//auto &unityRef = data[ foreachIndex ];
			for( singCaceIndex = 0; singCaceIndex < singCaceCount; singCaceIndex += 1 )
				if( comp_function( resultSingCaceData[ singCaceIndex ], data[ foreachIndex ] ) )
					break;
			if( singCaceIndex == singCaceCount ) { // 单例
				resultSingCaceData[ singCaceCount ] = data[ foreachIndex ];
				singCaceCount += 1;
			} else {
				for( repetitionIndex = 0; repetitionIndex < repetitionCount; repetitionIndex += 1 )
					if( comp_function( resultRepetionData[ repetitionIndex ], data[ foreachIndex ] ) )
						break;
				if( repetitionIndex < repetitionCount )
					continue;
				resultRepetionData[ repetitionCount ] = data[ foreachIndex ];
				repetitionCount += 1;
			}
		}
		result_repetion_vector.resize( repetitionCount );
		single_cace_vector.resize( singCaceCount );
		return repetitionCount;
	}

	/// @brief 释放序列元素
	/// @tparam UnityType_ 元素类型
	/// @param delete_vector_source 释放目标目标
	/// @return 释放个数
	template< typename UnityType_ >
	static size_t deleteVectorPtr( const std::vector< UnityType_ * > &delete_vector_source ) {
		auto count = delete_vector_source.size( );
		if( count == 0 )
			return count;
		decltype(count) index = 0;
		auto data = delete_vector_source.data( );
		for( ; index < count; index += 1 )
			delete data[ index ];
		return count;
	}

	/// @brief 去除空指针
	/// @tparam UnityType_ 元素指针类型
	/// @param result_vector_source 返回序列结果
	/// @param sort_vector_source 源序列
	/// @return 有效个数
	template< typename UnityType_ >
	static size_t removeNullptrVectorPtr( std::vector< UnityType_ * > &result_vector_source, const std::vector< UnityType_ * > &sort_vector_source ) {
		auto count = sort_vector_source.size( );
		if( count == 0 )
			return count;
		result_vector_source.resize( count );
		decltype(count) index = 0;
		decltype(count) setIndex = 0;
		auto data = sort_vector_source.data( );
		auto destData = result_vector_source.data( );

		for( ; index < count; index += 1 )
			if( data[ index ] ) {
				destData[ setIndex ] = data[ index ];
				setIndex += 1;
			}
		result_vector_source.resize( setIndex );
		return setIndex;
	}

	/// @brief 并集
	/// @tparam LeftUnityType_ 序列元素类型
	/// @param a_vector a 集合
	/// @param b_vector b 集合
	/// @param union_set_vector a 与 b 的并集
	template< typename LeftUnityType_ >
	static void unionSetVector( const std::vector< LeftUnityType_ > &a_vector, const std::vector< LeftUnityType_ > &b_vector, std::vector< LeftUnityType_ > &union_set_vector ) {
		if( &a_vector == &b_vector ) {
			union_set_vector = a_vector;
			return; // 相同集合，返回 a 或 b 集合
		}

		auto aCount = a_vector.size( );
		auto bCount = b_vector.size( );
		auto aData = a_vector.data( );
		auto bData = b_vector.data( );

		decltype(aData) onData;
		decltype(bData) inData;

		decltype(aCount) onCount;
		decltype(bCount) inCount;

		if( aCount > bCount ) {
			onCount = aCount;
			onData = aData;
			inCount = bCount;
			inData = bData;
		} else {
			onCount = bCount;
			onData = bData;
			inCount = aCount;
			inData = aData;
		}

		union_set_vector.resize( inCount );
		auto setData = union_set_vector.data( );
		decltype(inCount) setIndex = 0;

		decltype(aCount) onIndex;
		decltype(bCount) inIndex;

		for( onIndex = 0; onIndex < onCount; onIndex += 1 ) {
			for( inIndex = 0; inIndex < inCount; inIndex += 1 )
				if( inData[ inIndex ] == onData[ onIndex ] )
					break; // 匹配到相同
			if( inIndex == inCount )
				continue;
			setData[ setIndex ] = onData[ onIndex ];
			setIndex += 1;
		}
	}

	/// @brief 差集
	/// @tparam LeftUnityType_ 序列元素类型
	/// @param a_vector a 集合
	/// @param b_vector b 集合
	/// @param union_set_vector a 与 b 的并集
	template< typename LeftUnityType_ >
	static void differenceSetVector( const std::vector< LeftUnityType_ > &a_vector, const std::vector< LeftUnityType_ > &b_vector, std::vector< LeftUnityType_ > &union_set_vector ) {
		if( &a_vector == &b_vector ) {
			union_set_vector.clear( );
			return; // 相同集合，返回 a 或 b 集合
		}

		auto aCount = a_vector.size( );
		auto bCount = b_vector.size( );
		auto aData = a_vector.data( );
		auto bData = b_vector.data( );

		union_set_vector.resize( aCount );
		auto setData = union_set_vector.data( );
		decltype(aCount) setIndex = 0;

		decltype(aCount) onIndex;
		decltype(bCount) inIndex;

		for( onIndex = 0; onIndex < aCount; onIndex += 1 ) {
			for( inIndex = 0; inIndex < bCount; inIndex += 1 )
				if( bData[ inIndex ] == aData[ onIndex ] )
					break; // 匹配到相同
			if( inIndex != bCount )
				continue;
			setData[ setIndex ] = aData[ onIndex ];
			setIndex += 1;
		}
		union_set_vector.resize( setIndex );
	}

	/// @brief 检查序列是否元素单例，失败返回首个非单例下标
	/// @tparam Vector_Unity_Type_ 序列元素类型
	/// @param check 检测序列
	/// @param result_index 第一个非单例元素下标
	/// @return true 表示全员单例，不存在相同元素
	template< typename Vector_Unity_Type_ >
	bool isSingleCase( const std::vector< Vector_Unity_Type_ > &check, size_t &result_index ) {
		auto count = check.size( );
		if( count == 0 )
			return true;
		auto data = check.data( );
		decltype(count) findUnityIndex;

		decltype(count) currentUnityIndex;

		for( currentUnityIndex = 0; currentUnityIndex < count; currentUnityIndex += 1 )
			for( findUnityIndex = 0; findUnityIndex < count; findUnityIndex += 1 )
				if( findUnityIndex == currentUnityIndex )
					continue;
				else if( data[ currentUnityIndex ] == data[ findUnityIndex ] ) {
					result_index = currentUnityIndex;
					return false;
				}
		return true;
	}

	/// @brief 获取一个指针下标位置，失败返回 false
	/// @tparam Vector_Unity_Type_ 序列元素类型，必须为指针类型
	/// @param check 检查序列
	/// @param result_index 空指针下标
	/// @return 存在返回 true 并改变 result_index 值
	template< typename Vector_Unity_Type_ >
	bool hasNullptrUnity( const std::vector< Vector_Unity_Type_ * > &check, size_t &result_index ) {
		auto count = check.size( );
		if( count == 0 )
			return false;
		auto data = check.data( );
		decltype(count) currentUnityIndex;
		for( currentUnityIndex = 0; currentUnityIndex < count; currentUnityIndex += 1 )
			if( data[ currentUnityIndex ] == nullptr ) {
				result_index = currentUnityIndex;
				return true;
			}
		return false;
	}
};

#endif // VECTORTOOLS_H_H_HEAD__FILE__
