#ifndef CALCULATETOOLS_H_H_HEAD__FILE__
#define CALCULATETOOLS_H_H_HEAD__FILE__

class CalculateTools {
public:
	template< typename Var_Type >
	static Var_Type mod( const Var_Type &left, const Var_Type &right ) {
		Var_Type result = left;
		while( result > right )
			result -= right;
		return result;
	}
};

#endif // CALCULATETOOLS_H_H_HEAD__FILE__
