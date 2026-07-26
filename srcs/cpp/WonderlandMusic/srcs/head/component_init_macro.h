#ifndef COMPONENT_INIT_MACRO_H_H_HEAD__FILE__
#define COMPONENT_INIT_MACRO_H_H_HEAD__FILE__

#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include <QString>
#include <QObject>
/// @brief 调用一个组件指针对象进行初始化，失败返回 false
/// @param ptr 被调用初始化的指针对象
#define Init_Sub_Component_Ptr( ptr ) if( ptr == nullptr || ptr->initBefore( ) == false || ptr->init( ) == false || ptr->initAfter( ) == false) return ( Message_Error_Out << ( MessageString( ) << "Init_Sub_Component_Ptr( " << getTypeName( ptr ) << " * ") << #ptr<< " = "<< ptr << " )", false)

#endif // COMPONENT_INIT_MACRO_H_H_HEAD__FILE__
