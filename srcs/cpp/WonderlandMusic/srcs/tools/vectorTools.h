#ifndef VECTORTOOLS_H_H_HEAD__FILE__
#define VECTORTOOLS_H_H_HEAD__FILE__
#include <vector>

class VectorTools {
public:
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
};

#endif // VECTORTOOLS_H_H_HEAD__FILE__
