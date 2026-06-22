#ifndef AUTOMAKEPTRTOOLS_H_H_HEAD__FILE__
#define AUTOMAKEPTRTOOLS_H_H_HEAD__FILE__
#include <utility>

class AutoMakePtrTools {
public:
	template< typename Make_Type_, typename ...ptr_args >
	static Make_Type_ * makePtr( Make_Type_ *&ptr, const ptr_args && ...args ) {
		ptr = new Make_Type_( std::forward< ptr_args >( args ) ... );
		return ptr;
	}
};

#endif // AUTOMAKEPTRTOOLS_H_H_HEAD__FILE__
