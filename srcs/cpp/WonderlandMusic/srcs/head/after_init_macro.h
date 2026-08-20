#ifndef AFTER_INIT_MACRO_H_H_HEAD__FILE__
#define AFTER_INIT_MACRO_H_H_HEAD__FILE__

#include <tools/templateArgs.h>

#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include <QString>
#include <QObject>
#define After_Init_Resource_App_Core_Message_String_Ptr( ptr )  ((MessageString( ) << "After_Init_Resource_App_Core_Ptr( " << TemplateArgs::getTypeName( ptr ) << " * ") << #ptr<< " = "<< ptr << " )")
/// @brief 调用一个指针对象，进行初始化之后的操作，失败返回 false
/// @param ptr 被调用的指针对象
#define After_Init_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr || ptr->initAfter() == false ) return ( Message_Error_Out <<  After_Init_Resource_App_Core_Message_String_Ptr( ptr ), false)

#endif // AFTER_INIT_MACRO_H_H_HEAD__FILE__
