#ifndef CALL_CLASS_NATIVE_FUNCTION_H_H_HEAD__FILE__
#define CALL_CLASS_NATIVE_FUNCTION_H_H_HEAD__FILE__

/// @brief 调用一个指针对象函数
/// @param ptr 被调用的指针对象
#define Call_Ptr_Native_Class_Result_Bool_Type_Fcuntion( ptr, _call_ptr,_false_run_code ) \
	std::function< bool( ) >( \
		[this,ptr]( ) { \
			using CurrentType = std::remove_reference_t< decltype(*this) >; \
			if(ptr == nullptr ) \
				return true; \
			if( ptr->CurrentType::_call_ptr( ) ) \
				return true; \
			_false_run_code; \
			return false; \
		}\
		)( )
#endif // CALL_CLASS_NATIVE_FUNCTION_H_H_HEAD__FILE__
