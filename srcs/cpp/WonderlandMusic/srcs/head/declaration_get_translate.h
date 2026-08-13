#ifndef DECLARATION_GET_TRANSLATE_H_H_HEAD__FILE__
#define DECLARATION_GET_TRANSLATE_H_H_HEAD__FILE__

#define Declaration_Get_Translate( type_name_ ) \
	bool get##type_name_(const std::function< bool( type_name_##Translate & translate) > &translate_fun_call);

#endif // DECLARATION_GET_TRANSLATE_H_H_HEAD__FILE__
