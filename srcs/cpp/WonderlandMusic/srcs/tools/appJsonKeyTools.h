#ifndef APPJSONKEYTOOLS_H_H_HEAD__FILE__
#define APPJSONKEYTOOLS_H_H_HEAD__FILE__
#include <functional>
#include <head/head_json_key_class.h>
#define Declaration_Get_JsonKey( type_name_ ) \
	bool get##type_name_(const std::function< void( const type_name_##JsonKey & json_key) > &json_key_fun_call)

namespace AppJsonKeyTools {
	AppDataJsonKey * getAppJsonKey( );
	Declaration_Get_JsonKey( AboutWidget );
	Declaration_Get_JsonKey( MainWindow );
	Declaration_Get_JsonKey( SystemTrayIcon );
	Declaration_Get_JsonKey( AppDataManage );
	Declaration_Get_JsonKey( AppUserInterfaceManage );
	Declaration_Get_JsonKey( AppMusicManage );
};
#undef Declaration_Get_JsonKey
#endif // APPJSONKEYTOOLS_H_H_HEAD__FILE__
