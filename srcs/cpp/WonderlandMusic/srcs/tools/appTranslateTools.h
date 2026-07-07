#ifndef APPTRANSLATETOOLS_H_H_HEAD__FILE__
#define APPTRANSLATETOOLS_H_H_HEAD__FILE__
#include <functional>
#include <head/head_translate_class.h>
#define Declaration_Get_Translate( type_name_ ) \
	bool get##type_name_(const std::function< void( type_name_##Translate & translate) > &translate_fun_call);

namespace AppTranslateTools {
	AppTranslate * getAppTranslate( );
	Declaration_Get_Translate( SettingWidget );
	Declaration_Get_Translate( PlayerToolsWidget );
	Declaration_Get_Translate( PlayerListWidgetMenu );
	Declaration_Get_Translate( PlayerTopWidget );
	Declaration_Get_Translate( PlayerWindow );
	Declaration_Get_Translate( Json );
	Declaration_Get_Translate( DateTimeFormat );
	Declaration_Get_Translate( AboutWidget );
	Declaration_Get_Translate( MainWindow );
	Declaration_Get_Translate( Message );
	Declaration_Get_Translate( PlayerListWidget );
	Declaration_Get_Translate( MusicInfoItem );
	Declaration_Get_Translate( SystemTrayIconMenu );
	Declaration_Get_Translate( SystemTrayIcon );
	Declaration_Get_Translate( UserMutex );
	Declaration_Get_Translate( FavoriteWidget );
	Declaration_Get_Translate( OptionDockWidget );
	Declaration_Get_Translate( FavoriteWidgetMenu );
	Declaration_Get_Translate( AppMusicManage );
	Declaration_Get_Translate( DeleteException );
}
# undef  Declaration_Get_Translate
#endif // APPTRANSLATETOOLS_H_H_HEAD__FILE__
