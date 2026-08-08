#ifndef CREATE_PTR_MACRO_H_H_HEAD__FILE__
#define CREATE_PTR_MACRO_H_H_HEAD__FILE__

#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include <QString>
#include <QObject>

#define Create_Ptr_Resource_App_Core_Message_String_Ptr( ptr )  ((MessageString( ) << "Create_Ptr_Resource_App_Core_Ptr( " << getTypeName( ptr ) << " * ") << #ptr<< " = "<< ptr << " )")
/// @brief 调用一个指针对象，进行初始化之后的操作，失败返回 false
/// @param ptr 被调用的指针对象
#define Create_Ptr_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr  ) return ( Message_Error_Out <<  Create_Ptr_Resource_App_Core_Message_String_Ptr( ptr ), false)
#endif // CREATE_PTR_MACRO_H_H_HEAD__FILE__
