#include "invokeMethodTools.h"

#include "instanceTools.h"

#include "../application/appInstance/applicationManage.h"

#include "../head/result_message_out.h"

#include "../thread/musicPlayerThread/musicMediaPlayerThread.h"

namespace invoke {
	static void work( ApplicationManage *applicationManage, const std::function< void( ApplicationManage *applicationManage ) > &function ) {
		function( applicationManage );
	}
	static bool method( const std::function< void( ApplicationManage *applicationManage ) > &function, Qt::ConnectionType type ) {
		ApplicationManage *applicationManage = InstanceTools::getApplicationManage( );
		if( applicationManage == nullptr )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, applicationManage, InstanceTools::getApplicationManage, QObject::tr( "找不到实例" ) );
		bool invokeMethod = QMetaObject::invokeMethod( applicationManage, [function, applicationManage]( ) {
			work( applicationManage, function );
		}, type );

		if( invokeMethod == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, applicationManage, invoke::method, QObject::tr( "调用失败" ) );
		return true;
	}
}

bool InvokeMethodTools::invokeQueuedConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function ) {
	return invoke::method( function, Qt::QueuedConnection );
}

bool InvokeMethodTools::invokeAutoConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function ) {
	return invoke::method( function, Qt::AutoConnection );
}
bool InvokeMethodTools::invokeDirectConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function ) {
	return invoke::method( function, Qt::DirectConnection );
}
bool InvokeMethodTools::invokeBlockingQueuedConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function ) {
	return invoke::method( function, Qt::BlockingQueuedConnection );
}
bool InvokeMethodTools::invokeUniqueConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function ) {
	return invoke::method( function, Qt::UniqueConnection );
}
bool InvokeMethodTools::invokeSingleShotConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function ) {
	return invoke::method( function, Qt::SingleShotConnection );
}
