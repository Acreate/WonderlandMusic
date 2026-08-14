#ifndef COMPONENT_ASSERT_MACRO_H_H_HEAD__FILE__
#define COMPONENT_ASSERT_MACRO_H_H_HEAD__FILE__

#include <tools/templateArgs.h>

#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include <QString>
#include <QObject>
/// @brief 调用一个组件指针对象函数进行初始化，失败返回 false
/// @param ptr 被调用初始化的指针对象
#define Component_Call_Fun_Assert_Ptr( ptr, if_assert ) do{auto var_ptr = ptr; if( var_ptr && var_ptr->if_assert ) break;  Message_Error_Out << ( MessageString( ) << "Component_Assert_Ptr( " << TemplateArgs::getTypeName( var_ptr ) << " * ") << #ptr << " = "<< ptr << " ) " << #ptr "->" #if_assert; return false ;}while(false)

#endif // COMPONENT_ASSERT_MACRO_H_H_HEAD__FILE__
