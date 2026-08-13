#ifndef DEFININITION_GET_TRANSLATE_H_H_HEAD__FILE__
#define DEFININITION_GET_TRANSLATE_H_H_HEAD__FILE__

#define Defininition_Get_Translate( type_name_ ) \
	bool AppTranslateTools::get##type_name_(const std::function< bool( type_name_##Translate & translate) > &translate_fun_call){\
		type_name_##Translate *var = nullptr; \
		AppTranslate *appTranslate = AppTranslateTools::getAppTranslate( ); \
		if( appTranslate ){ \
			var = appTranslate->get##type_name_( );\
			if( var ) { \
				auto result = translate_fun_call( *var ); \
				return result; \
			}\
		}\
		var = new type_name_##Translate; \
		if( var->init( ) ) { \
			auto result = translate_fun_call( *var ); \
			delete var; \
			return result; \
		} \
		return false;\
	}

#endif // DEFININITION_GET_TRANSLATE_H_H_HEAD__FILE__
