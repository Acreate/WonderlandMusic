#ifndef INIT_MACRO_H_H_HEAD__FILE__
#define INIT_MACRO_H_H_HEAD__FILE__

#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include <QString>
#include <QObject>

#define Init_Resource_App_Core_Message_String_Ptr( ptr ) ((MessageString( ) << "Init_Resource_App_Core_Ptr( " << getTypeName( ptr ) << " * ") << #ptr<< " = "<< ptr << " )")
/// @brief 调用一个指针对象进行初始化，失败返回 false
/// @param ptr 被调用初始化的指针对象
#define Init_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr || ptr->init() == false ) return ( Message_Error_Out <<  Init_Resource_App_Core_Message_String_Ptr( ptr ) , false)

#endif // INIT_MACRO_H_H_HEAD__FILE__
