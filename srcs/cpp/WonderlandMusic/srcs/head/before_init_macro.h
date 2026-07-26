#ifndef BEFORE_INIT_MACRO_H_H_HEAD__FILE__
#define BEFORE_INIT_MACRO_H_H_HEAD__FILE__

#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include <QString>
#include <QObject>
/// @brief 调用一个指针对象，进行初始化之前操作，失败返回 false
/// @param ptr 被调用的指针对象
#define Before_Init_Resource_App_Core_Ptr( ptr ) if( ptr == nullptr || ptr->initBefore() == false ) return ( Message_Error_Out << ( MessageString( ) << "Before_Init_Resource_App_Core_Ptr( " << getTypeName( ptr ) << " * ") << #ptr<< " = "<< ptr << " )", false)

#endif // BEFORE_INIT_MACRO_H_H_HEAD__FILE__
