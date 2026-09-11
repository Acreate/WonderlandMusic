#ifndef INVOKEMETHODTOOLS_H_H_HEAD__FILE__
#define INVOKEMETHODTOOLS_H_H_HEAD__FILE__
#include <functional>

class ApplicationManage;

namespace InvokeMethodTools {
	bool invokeQueuedConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function );
	bool invokeAutoConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function );
	bool invokeDirectConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function );
	bool invokeBlockingQueuedConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function );
	bool invokeUniqueConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function );
	bool invokeSingleShotConnectionMethod( const std::function< void( ApplicationManage *applicationManage ) > &function );
}

#endif // INVOKEMETHODTOOLS_H_H_HEAD__FILE__
