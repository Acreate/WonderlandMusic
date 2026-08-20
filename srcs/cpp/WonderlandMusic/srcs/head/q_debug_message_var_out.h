#ifndef Q_DEBUG_MESSAGE_VAR_OUT_H_H_HEAD__FILE__
#define Q_DEBUG_MESSAGE_VAR_OUT_H_H_HEAD__FILE__

#define Var_Name_MessageString( _var ) \
	( MessageString( std::source_location::current( ) ) << "\n\t" << #_var << " = " << _var )
#define Q_Debug_Var_Nmae_MessageString( _var ) \
	qDebug( ) << "------\n" << ( Var_Name_MessageString( _var ).toQString(  ).toStdString(  ).c_str(  ) ) << "\n------"
#endif // Q_DEBUG_MESSAGE_VAR_OUT_H_H_HEAD__FILE__
