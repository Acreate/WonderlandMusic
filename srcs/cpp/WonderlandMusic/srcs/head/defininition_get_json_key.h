#ifndef DEFININITION_GET_JSON_KEY_H_H_HEAD__FILE__
#define DEFININITION_GET_JSON_KEY_H_H_HEAD__FILE__

#define Defininition_Get_Json_Key( type_name_ ) \
	bool AppJsonKeyTools::get##type_name_(const std::function< void(const type_name_##JsonKey & json_key) > &json_key_fun_call){\
		type_name_##JsonKey *var = nullptr; \
		auto *getPtr = AppJsonKeyTools::getAppJsonKey( ); \
		if( getPtr ){ \
			var = getPtr->get##type_name_( );\
			if( var ) { \
				json_key_fun_call( *var ); \
				return true; \
			}\
		}\
		var = new type_name_##JsonKey( ); \
		if( var->init( ) ) { \
			json_key_fun_call( *var ); \
			delete var; \
			return true; \
		} \
		return false;\
	}
#endif // DEFININITION_GET_JSON_KEY_H_H_HEAD__FILE__
