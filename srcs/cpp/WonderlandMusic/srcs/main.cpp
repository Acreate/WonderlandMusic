#include "initMain.h"

#include "head/result_message_out.h"
int main( int argc, char *argv[ ], char *envp[ ] ) {
	InitMain *initMain = new InitMain( argc, argv, envp );
	if( initMain->initBefore( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( initMain->getExecCode( ), initMain, initBefore, QObject::tr( "生成工作环境异常" ) );
	if( initMain->init( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( initMain->getExecCode( ), initMain, init, QObject::tr( "初始化工作环境异常" ) );
	if( initMain->initAfter( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( initMain->getExecCode( ), initMain, initAfter, QObject::tr( "准备工作环境异常" ) );
	int runMainCode = initMain->runMain( );
	delete initMain;
	return runMainCode;
}
