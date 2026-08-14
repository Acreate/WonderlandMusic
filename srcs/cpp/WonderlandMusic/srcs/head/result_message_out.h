#ifndef RESULT_MESSAGE_OUT_H_H_HEAD__FILE__
#define RESULT_MESSAGE_OUT_H_H_HEAD__FILE__
#include <tools/templateArgs.h>
#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include <QString>
#include <QObject>
#define Result_Var_Messag_Out_Ptr_Function( ptr, _function )  ((MessageString( ) << TemplateArgs::getTypeName( ptr ) << "::" #_function "( " << TemplateArgs::getTypeName( ptr ) << " * ") << #ptr<< " = "<< ptr << " )")

#define Result_Var_Messag_Out_Call_Function( ptr, call, _function )  ((MessageString( ) << #call "::" #_function "( " << TemplateArgs::getTypeName( ptr ) << " * ") << #ptr<< " = "<< ptr << " )")

#define Result_Var_Messag_Ptr_Fcuntion_Out( _result_var , _ptr, _function ) ( Message_Error_Out <<  Result_Var_Messag_Out_Ptr_Function( _ptr ,_function ), _result_var )

#define Result_Var_Messag_Call_Fcuntion_Out( _result_var , _ptr, _call ,_function ) ( Message_Error_Out <<  Result_Var_Messag_Out_Call_Function(_ptr, _call ,_function ), _result_var )

#endif // RESULT_MESSAGE_OUT_H_H_HEAD__FILE__
