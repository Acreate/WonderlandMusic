cmake_minimum_required( VERSION 3.19 )

# # 打印输出 qt 环境
function( printf_qt_cmake_out )
	message( "QT_VERSION = ${QT_VERSION}" )
	message( "QT_VERSION_MAJOR = ${QT_VERSION_MAJOR}" )
	message( "DEPLOY_QT_HOME = ${DEPLOY_QT_HOME}" )
	message( "Qt6_DIR = ${Qt6_DIR}" )
	message( "Qt${QT_VERSION_MAJOR}CoreTools_DIR = ${Qt${QT_VERSION_MAJOR}CoreTools_DIR}" )
	message( "Qt${QT_VERSION_MAJOR}GuiTools_DIR = ${Qt${QT_VERSION_MAJOR}GuiTools_DIR}" )
	message( "Qt${QT_VERSION_MAJOR}WidgetsTools_DIR = ${Qt${QT_VERSION_MAJOR}WidgetsTools_DIR}" )
	message( "Qt${QT_VERSION_MAJOR}Widgets_DIR = ${Qt${QT_VERSION_MAJOR}Widgets_DIR}" )
	message( "Qt${QT_VERSION_MAJOR}ZlibPrivate_DIR = ${Qt${QT_VERSION_MAJOR}ZlibPrivate_DIR}" )
	message( "Qt${QT_VERSION_MAJOR}Core_DIR = ${Qt${QT_VERSION_MAJOR}Core_DIR}" )
	message( "WINDEPLOYQT_EXECUTABLE = ${WINDEPLOYQT_EXECUTABLE}" )
	message( "QT_QMAKE_EXECUTABLE = ${QT_QMAKE_EXECUTABLE}" )
endfunction( )

# # 生成 qt 安装脚本
# # target_obj 生成脚本的目标
function( qt_generate_deploy_cmake_script_inatll_job _out_deploy_script_job_path target_obj )
	if( qt_FOUND EQUAL 0 )
		message( "未成功初始化该模块，请定义 Qt6_DIR 后在初始化模块" )
		return( )
	endif( )
	
	get_target_property( projectType "${target_obj}" TYPE )
	
	if( "${projectType}" STREQUAL "EXECUTABLE" )
		get_target_property( Project_Run_Bin_Path "${target_obj}" RUNTIME_OUTPUT_DIRECTORY )
		message( "生成 [可自行文件] 路径 = ${Project_Run_Bin_Path}" )
	else( )
		get_target_property( Project_Run_Bin_Path "${target_obj}" LIBRARY_OUTPUT_DIRECTORY )
		message( "生成 [动态库] 路径 = ${Project_Run_Bin_Path}" )
	endif( )
	
	# App bundles on macOS have an .app suffix
	if( APPLE )
		set( executable_path "$<TARGET_FILE_NAME:${target_obj}>.app" )
	else( )
		set( executable_path "${Project_Run_Bin_Path}/$<TARGET_FILE_NAME:${target_obj}>" )
	endif( )
	
	qt_generate_deploy_script(
		TARGET ${target_obj}
		OUTPUT_SCRIPT deploy_script
		CONTENT "
include( \"\\$\{CMAKE_CURRENT_LIST_DIR\}/$<TARGET_FILE_BASE_NAME:${target_obj}>-plugins.cmake\" OPTIONAL )
include( \"\\$\{CMAKE_CURRENT_LIST_DIR\}/QtDeploySupport.cmake\" OPTIONAL )

message( \"导入 : \\$\{CMAKE_CURRENT_LIST_DIR\}/$<TARGET_FILE_BASE_NAME:${target_obj}>-plugins.cmake\" )
message( \"导入 : \\$\{CMAKE_CURRENT_LIST_DIR\}/QtDeploySupport.cmake\" )
message( \"打包程序 : ${executable_path}\" )
set( QT_DEPLOY_PREFIX  \"${Project_Run_Bin_Path}\" )
# set( QT_DEPLOY_PREFIX \"\\$\{QT_DEPLOY_PREFIX\}\" PARENT_SCOPE )
qt_deploy_runtime_dependencies(
    EXECUTABLE \"${executable_path}\"
	PLUGINS_DIR \"${Project_Run_Bin_Path}\"
	LIB_DIR \"${Project_Run_Bin_Path}\"
	BIN_DIR \"${Project_Run_Bin_Path}\"
    NO_OVERWRITE
)
message( \"完成程序 : ${executable_path}\" )
" )
	
	install( SCRIPT ${deploy_script} )
	set( ${_out_deploy_script_job_path} ${deploy_script} PARENT_SCOPE )
endfunction( )

# # 更新 qt 路基
# # qt_dir 指定路径，或者 Qt6_DIR 变量已经实现
function( update_qt_dir_event qt_dir )
	if( NOT qt_dir OR NOT EXISTS "${qt_dir}" )
		if( NOT Qt6_DIR AND NOT EXISTS "${Qt6_DIR}" )
			message( "路径不存在，请为 qt_dir 参数提供有效的路径或者使用有效的 Qt6_DIR 变量实现定义" )
		else( )
			set( qt_dir "${Qt6_DIR}" PARENT_SCOPE )
			message( "正在使用有效的 Qt6_DIR 变量实现定义 = ${Qt6_DIR}" )
		endif( )
		
		return( )
	endif( )
	
	set( Qt6_DIR "${qt_dir}" PARENT_SCOPE )
	set( Qt_DIR "${Qt6_DIR}" PARENT_SCOPE )
	set( qt_DIR "${Qt6_DIR}" PARENT_SCOPE )
	
	get_filename_component( _absParamFilePath "${Qt6_DIR}" ABSOLUTE )
	
	get_cmake_separator( _sep )
	string_splite( _splite_dir_name "${_absParamFilePath}" "${_sep}" )
	
	list( GET _splite_dir_name -5 _result ) # # 版本文件夹
	
	string_splite( _versionSplite "${_result}" "." )
	
	list( GET _versionSplite 0 QT_VERSION_MAJOR ) # # 获取主要版本
	set( QT_VERSION_MAJOR "${QT_VERSION_MAJOR}" PARENT_SCOPE )
	
	set( QT_VERSION "${_result}" PARENT_SCOPE )
	
	list( GET _splite_dir_name -4 _builder_tools )
	set( DEPLOY_QT_HOME "C:/Qt/${QT_VERSION}/${_builder_tools}/" PARENT_SCOPE )
	set( WINDEPLOYQT_EXECUTABLE "${DEPLOY_QT_HOME}/bin/windeployqt.exe" PARENT_SCOPE )
	set( QT_QMAKE_EXECUTABLE "${DEPLOY_QT_HOME}/bin/qmake.exe" PARENT_SCOPE )
	set( Qt${QT_VERSION_MAJOR}CoreTools_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}CoreTools" PARENT_SCOPE )
	set( Qt${QT_VERSION_MAJOR}GuiTools_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}GuiTools" PARENT_SCOPE )
	set( Qt${QT_VERSION_MAJOR}WidgetsTools_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}WidgetsTools" PARENT_SCOPE )
	set( Qt${QT_VERSION_MAJOR}Widgets_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}Widgets" PARENT_SCOPE )
	set( Qt${QT_VERSION_MAJOR}ZlibPrivate_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}ZlibPrivate" PARENT_SCOPE )
	set( Qt${QT_VERSION_MAJOR}Core_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}Core" PARENT_SCOPE )
	
	# qt 资源自动编译
	set( CMAKE_AUTOMOC ON PARENT_SCOPE )
	set( CMAKE_AUTOUIC ON PARENT_SCOPE )
	set( CMAKE_AUTORCC ON PARENT_SCOPE )
	
endfunction( )

# # 更新 qt 路基，当环境已经实现时，该调用直接返回
# # qt_dir 指定路径，或者 Qt6_DIR 变量已经实现
function( init_qt_dir_event qt_dir )
	check_value_is_define( _result _CHECK_CMAKE_VALUE_ Qt6_DIR qt_DIR QT_VERSION_MAJOR QT_VERSION DEPLOY_QT_HOME CMAKE_PREFIX_PATH WINDEPLOYQT_EXECUTABLE QT_QMAKE_EXECUTABLE Qt${QT_VERSION_MAJOR}CoreTools_DIR Qt${QT_VERSION_MAJOR}GuiTools_DIR Qt${QT_VERSION_MAJOR}WidgetsTools_DIR Qt${QT_VERSION_MAJOR}Widgets_DIR Qt${QT_VERSION_MAJOR}ZlibPrivate_DIR Qt${QT_VERSION_MAJOR}Core_DIR )
	
	if( NOT _result )
		message( "<------------------>" )
		message( "qt cmake 已经实现配置" )
		message( "<------------------>" )
		return( )
	else( )
		list( JOIN _result ", " _not_def_var )
		message( "<------------------>" )
		message( "正在配置列表 : ${_not_def_var}" )
		message( "<------------------>" )
	endif( )
	
	if( NOT qt_dir OR NOT EXISTS "${qt_dir}" )
		if( NOT Qt6_DIR AND NOT EXISTS "${Qt6_DIR}" )
			message( "路径不存在，请为 qt_dir 参数提供有效的路径或者使用有效的 Qt6_DIR 变量实现定义" )
		else( )
			set( qt_dir "${Qt6_DIR}" PARENT_SCOPE )
			message( "正在使用有效的 Qt6_DIR 变量实现定义 = ${Qt6_DIR}" )
		endif( )
		
		return( )
	endif( )
	
	if( NOT Qt6_DIR )
		set( Qt6_DIR "${qt_dir}" PARENT_SCOPE )
	endif( )
	
	if( NOT Qt_DIR )
		set( Qt_DIR "${Qt6_DIR}" PARENT_SCOPE )
	endif( )
	
	if( NOT qt_DIR )
		set( qt_DIR "${Qt6_DIR}" PARENT_SCOPE )
	endif( )
	
	get_filename_component( _absParamFilePath "${Qt6_DIR}" ABSOLUTE )
	
	get_cmake_separator( _sep )
	string_splite( _splite_dir_name "${_absParamFilePath}" "${_sep}" )
	
	list( GET _splite_dir_name -5 _result ) # # 版本文件夹
	
	string_splite( _versionSplite "${_result}" "." )
	
	if( NOT QT_VERSION_MAJOR )
		list( GET _versionSplite 0 QT_VERSION_MAJOR ) # # 获取主要版本
		set( QT_VERSION_MAJOR "${QT_VERSION_MAJOR}" PARENT_SCOPE )
	endif( )
	
	if( NOT QT_VERSION )
		set( QT_VERSION "${_result}" PARENT_SCOPE )
	endif( )
	
	if( NOT DEPLOY_QT_HOME )
		list( GET _splite_dir_name -4 _builder_tools )
		set( DEPLOY_QT_HOME "C:/Qt/${QT_VERSION}/${_builder_tools}/" PARENT_SCOPE )
	endif( )
	
	if( NOT WINDEPLOYQT_EXECUTABLE )
		set( WINDEPLOYQT_EXECUTABLE "${DEPLOY_QT_HOME}/bin/windeployqt.exe" PARENT_SCOPE )
	endif( )
	
	if( NOT QT_QMAKE_EXECUTABLE )
		set( QT_QMAKE_EXECUTABLE "${DEPLOY_QT_HOME}/bin/qmake.exe" PARENT_SCOPE )
	endif( )
	
	if( NOT Qt${QT_VERSION_MAJOR}CoreTools_DIR )
		set( Qt${QT_VERSION_MAJOR}CoreTools_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}CoreTools" PARENT_SCOPE )
	endif( )
	
	if( NOT Qt${QT_VERSION_MAJOR}GuiTools_DIR )
		set( Qt${QT_VERSION_MAJOR}GuiTools_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}GuiTools" PARENT_SCOPE )
	endif( )
	
	if( NOT Qt${QT_VERSION_MAJOR}WidgetsTools_DIR )
		set( Qt${QT_VERSION_MAJOR}WidgetsTools_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}WidgetsTools" PARENT_SCOPE )
	endif( )
	
	if( NOT Qt${QT_VERSION_MAJOR}Widgets_DIR )
		set( Qt${QT_VERSION_MAJOR}Widgets_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}Widgets" PARENT_SCOPE )
	endif( )
	
	if( NOT Qt${QT_VERSION_MAJOR}ZlibPrivate_DIR )
		set( Qt${QT_VERSION_MAJOR}ZlibPrivate_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}ZlibPrivate" PARENT_SCOPE )
	endif( )
	
	if( NOT Qt${QT_VERSION_MAJOR}Core_DIR )
		set( Qt${QT_VERSION_MAJOR}Core_DIR "${DEPLOY_QT_HOME}/lib/cmake/Qt${QT_VERSION_MAJOR}Core" PARENT_SCOPE )
	endif( )
	
	set( CMAKE_AUTOUIC ON PARENT_SCOPE )
	set( CMAKE_AUTOMOC ON PARENT_SCOPE )
	set( CMAKE_AUTORCC ON PARENT_SCOPE )
endfunction( )

get_filename_component( abs "${CMAKE_CURRENT_LIST_FILE}" ABSOLUTE )
string( FIND "${abs}" "${CMAKE_HOME_DIRECTORY}" index )

if( NOT ${index} EQUAL -1 )
	string( LENGTH "${abs}" _orgStrLen )
	string( LENGTH "${CMAKE_HOME_DIRECTORY}" _findStrLen )
	math( EXPR _subLen "${_orgStrLen} - ${_findStrLen}" )
	string( SUBSTRING "${abs}" ${_findStrLen} ${_subLen} abs )
	set( abs ".${abs}" )
endif( )

message( "----\n\t\t调用:(${abs}[${CMAKE_CURRENT_FUNCTION}]:${CMAKE_CURRENT_LIST_LINE})行 ->\n\t\t\t消息:列表加载完毕" )
