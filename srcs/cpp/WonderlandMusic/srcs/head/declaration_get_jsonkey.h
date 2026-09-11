#ifndef DECLARATION_GET_JSONKEY_H_H_HEAD__FILE__
#define DECLARATION_GET_JSONKEY_H_H_HEAD__FILE__

#define Declaration_Get_JsonKey( type_name_ ) \
	bool get##type_name_(const std::function< bool( const type_name_##JsonKey & json_key) > &json_key_fun_call)

#endif // DECLARATION_GET_JSONKEY_H_H_HEAD__FILE__
