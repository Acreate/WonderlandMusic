#ifndef AUTOMAKEPTRTOOLS_H_H_HEAD__FILE__
#define AUTOMAKEPTRTOOLS_H_H_HEAD__FILE__
#include <utility>

namespace AutoMakePtrTools {
	template< typename Make_Type_, typename ...ptr_args >
	Make_Type_ * makePtr( Make_Type_ *&ptr, ptr_args && ...args ) {
		ptr = new Make_Type_( std::forward< ptr_args >( args ) ... );
		return ptr;
	}
}

#endif // AUTOMAKEPTRTOOLS_H_H_HEAD__FILE__
