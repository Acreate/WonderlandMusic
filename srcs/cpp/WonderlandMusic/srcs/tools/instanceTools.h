#ifndef INSTANCETOOLS_H_H_HEAD__FILE__
#define INSTANCETOOLS_H_H_HEAD__FILE__

#define Def_Get_Name_Function( _type ) class _type; namespace InstanceTools { _type * get##_type( ); }

Def_Get_Name_Function( AppDataManage );

Def_Get_Name_Function( AppDataJsonKey );

Def_Get_Name_Function( AppDateTimerManage );

Def_Get_Name_Function( AppDrawManage );

Def_Get_Name_Function( AppInstance );

Def_Get_Name_Function( ApplicationManage );

Def_Get_Name_Function( AppMenuManage );

Def_Get_Name_Function( AppMusicDecoder );

Def_Get_Name_Function( AppMusicManage );

Def_Get_Name_Function( AppRenderImage );

Def_Get_Name_Function( AppTranslate );

Def_Get_Name_Function( AppUserInterfaceManage );

#endif // INSTANCETOOLS_H_H_HEAD__FILE__
