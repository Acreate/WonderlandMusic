#ifndef VECTORTOOLS_H_H_HEAD__FILE__
#define VECTORTOOLS_H_H_HEAD__FILE__
#include <functional>
#include <vector>

class VectorTools {
public:
	/// @brief 查找元素
	/// @tparam UnityType_ 序列元素类型
	/// @param find_vector_source 查找源
	/// @param find_var_target 查找目标
	/// @param result_index 目标下标
	/// @return 不存在返回 false
	template< typename UnityType_ >
	static bool findIndex( const std::vector< UnityType_ > &find_vector_source, const UnityType_ &find_var_target, size_t &result_index ) {
		auto count = find_vector_source.size( );
		if( count == 0 )
			return false;
		auto data = find_vector_source.data( );
		result_index = 0;
		for( ; result_index < count; ++result_index )
			if( data[ result_index ] == find_var_target )
				return true;
		return false;
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
};

#endif // VECTORTOOLS_H_H_HEAD__FILE__
