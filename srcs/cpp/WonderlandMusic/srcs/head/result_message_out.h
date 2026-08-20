#ifndef RESULT_MESSAGE_OUT_H_H_HEAD__FILE__
#define RESULT_MESSAGE_OUT_H_H_HEAD__FILE__
#include <tools/templateArgs.h>
#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include <QString>
#include <QObject>

#define Txt( _var ) QString(#_var)
#define Result_Var_Function_Messag_Ptr_Out_Args( _result_var , _ptr, _function , ... ) (( Message_Error_Out <<  ( MessageString( ) <<  "#0x" << MessageString( _ptr )<< "->" << TemplateArgs::getTypeName( _ptr ) << "::" << #_function << " ! [ " << MessageString( QStringList{ __VA_ARGS__ } ) << " ]")), _result_var )
#define Result_Void_Function_Messag_Ptr_Out_Args(  _ptr, _function , ... ) do{ Message_Error_Out <<  ( MessageString( ) <<  "#0x" << MessageString( _ptr )<< "->" << TemplateArgs::getTypeName( _ptr ) << "::" << #_function << " ! [ " << MessageString( QStringList{ __VA_ARGS__ } ) << " ]") ; return ;}while(false)

#define Result_Var_Messag_Ptr_Out_Args( _result_var , _ptr, ... ) (( Message_Error_Out <<  ( MessageString( ) <<  "#0x" << MessageString( _ptr )<< "->" << TemplateArgs::getTypeName( _ptr ) << "::" << __FUNCTION__ << " ! [ " << MessageString( QStringList{ __VA_ARGS__ } ) << " ]")), _result_var )
#define Result_Void_Messag_Ptr_Out_Args(  _ptr , ... ) do{ Message_Error_Out <<  ( MessageString( ) <<  "#0x" << MessageString( _ptr )<< "->" << TemplateArgs::getTypeName( _ptr ) << "::" << __FUNCTION__ << " ! [ " << MessageString( QStringList{ __VA_ARGS__ } ) << " ]") ; return ;}while(false)
#endif // RESULT_MESSAGE_OUT_H_H_HEAD__FILE__
