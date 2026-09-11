cmake_minimum_required( VERSION 3.19 )

# # 获取路径的全路径
function( get_absolute_path result_dir_path in_path )
	get_filename_component( absolutePath "${in_path}" ABSOLUTE ) # 全路径
	set( ${result_dir_path} "${absolutePath}" PARENT_SCOPE )
endfunction( )

# # 配置标准路径变量
# # Project_Run_Bin_Path : 二进制路径
# # Project_Run_Pbd_Path : 调试路径
# # Project_Run_Static_Lib_Path : 静态库目录
# # Project_Install_Path : 安装目录
function( init_std_builder_path )
	set( processor_ver )
	
	if( CMAKE_SYSTEM_PROCESSOR MATCHES "x86|i686" )
		set( processor_ver x86 )
	elseif( CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64" )
		set( processor_ver x86_64 )
	endif( )
	
	set( Project_Run_Bin_Path "${CMAKE_HOME_DIRECTORY}/builder/${CMAKE_BUILD_TYPE}/${processor_ver}_${CMAKE_CXX_COMPILER_ID}_bin/" )
	set( Project_Run_Pbd_Path "${CMAKE_HOME_DIRECTORY}/builder/${CMAKE_BUILD_TYPE}/${processor_ver}_${CMAKE_CXX_COMPILER_ID}_pbd/" )
	set( Project_Run_Static_Lib_Path "${CMAKE_HOME_DIRECTORY}/builder/${CMAKE_BUILD_TYPE}/${processor_ver}_${CMAKE_CXX_COMPILER_ID}_lib/" )
	set( Project_Install_Path "${CMAKE_HOME_DIRECTORY}/builder/install/" )
	
	set( Project_Run_Bin_Path "${Project_Run_Bin_Path}" PARENT_SCOPE )
	set( Project_Run_Pbd_Path "${Project_Run_Pbd_Path}" PARENT_SCOPE )
	set( Project_Run_Static_Lib_Path "${Project_Run_Static_Lib_Path}" PARENT_SCOPE )
	set( Project_Install_Path "${Project_Install_Path}" PARENT_SCOPE )
endfunction( )

# ## 根据目录获取一个文件夹名称
function( get_current_dir_name out_name in_path )
	string( REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${in_path} )
	set( ${out_name} ${CURRENT_FOLDER} PARENT_SCOPE )
endfunction( )

# ## 根据目录获取一个文件夹名称
function( get_parent_dir_name out_name in_path )
	string( REGEX REPLACE ".*/(.*)/(.*)" "\\1" CURRENT_FOLDER ${in_path} )
	set( ${out_name} ${CURRENT_FOLDER} PARENT_SCOPE )
endfunction( )

# ## 在目录中查找目录，并且在目标目录中找到 file_name 的文件名
# ## 若存在，则返回所在目录的路径
# ## 文件名不区分大小写
function( get_path_cmake_dir_path out_list check_path_dir file_name )
	set( for_each_list_dirs ${${out_list}} )
	
	if( IS_DIRECTORY "${check_path_dir}" )
		# # 获取所有目录
		file( GLOB_RECURSE file_get_file_paths "${check_path_dir}/*" )
		
		foreach( current_path_file ${file_get_file_paths} )
			string( REGEX REPLACE ".+/(.*)" "\\1" out_file_name ${current_path_file} )
			
			if( "${file_name}" STREQUAL "${out_file_name}" )
				string( REGEX REPLACE "(.+)/.*" "\\1" out_path_file ${current_path_file} )
				list( APPEND for_each_list_dirs "${out_path_file}" )
			endif( )
		endforeach( )
		
		set( ${out_list} ${for_each_list_dirs} PARENT_SCOPE )
	endif( )
endfunction( )

# # 查找指定路径的源码文件
# # out_file_list : 返回值
# # PATH : 指定单个路径
# # LANGUAGES : 查找的编程语言
# # SUFFIX : 追加的后缀。可以多个
function( get_path_sources out_file_list )
	set( OPTIONAL )
	set( oneValueArgs )
	set( multiValueArgs LANGUAGES SUFFIXS PATHS )
	cmake_parse_arguments( arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
	
	set( for_each_list_dirs ${${out_file_list}} )
	
	foreach( language ${arg_LANGUAGES} )
		check_language( ${language} )
		
		if( NOT CMAKE_${language}_COMPILER )
			message( "不支持 ${language} 开发环境，请重新检查" )
			continue( )
		endif( )
		
		foreach( all_suffix ${CMAKE_${language}_SOURCE_FILE_EXTENSIONS} )
			list( APPEND arg_SUFFIXS "${all_suffix}" )
		endforeach( )
	endforeach( )
	
	foreach( satrt_path ${arg_PATHS} )
		foreach( arg_suffix ${arg_SUFFIXS} )
			string_splite( _splite_list "${arg_suffix}" "." )
			list( GET _splite_list -1 _result_suffix )
			list( APPEND suffix "${satrt_path}/*.${_result_suffix}" )
		endforeach( )
	endforeach( )
	
	file( GLOB_RECURSE for_each_file_list ${suffix} )
	
	set( ${out_file_list} ${for_each_file_list} PARENT_SCOPE )
endfunction( )

# # 查找指定路径的 *.cpp *.c *.hpp *.h 文件
# # check_path : 路径
# # out_file_list : 返回值
function( get_path_cxx_and_c_sources out_file_list check_path )
	check_language( C )
	check_language( CXX )
	
	if( NOT CMAKE_CXX_COMPILER AND NOT CMAKE_C_COMPILER AND EXISTS "${CMAKE_CXX_COMPILER}" AND EXISTS "${CMAKE_C_COMPILER}" )
		message( "\t\t!!! 当前 cmake 环境并不支持 C/C++ ，请重新检查开发环境" )
		return( )
	endif( )
	
	set( for_each_list_dirs ${${out_file_list}} )
	
	foreach( cpp_suffix ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS} )
		string_splite( _splite_list "${cpp_suffix}" "." )
		list( GET _splite_list -1 _result_suffix )
		list( APPEND suffix "${check_path}/*.${_result_suffix}" )
	endforeach( )
	
	foreach( c_suffix ${CMAKE_C_SOURCE_FILE_EXTENSIONS} )
		string_splite( _splite_list "${c_suffix}" "." )
		list( GET _splite_list -1 _result_suffix )
		list( APPEND suffix "${check_path}/*.${_result_suffix}" )
	endforeach( )
	
	file( GLOB_RECURSE for_each_file_list ${suffix} )
	
	set( ${out_file_list} ${for_each_file_list} PARENT_SCOPE )
endfunction( )

# ## 使用全局的安装文件方式拷贝文件
# ## @dest_dir_path 目标目录
# ## @... 多个文件
function( user_install_copy_file dest_dir_path )
	math( EXPR resultIndex "${ARGC}-1" OUTPUT_FORMAT DECIMAL )
	
	foreach( item RANGE 1 ${resultIndex} )
		list( GET ARGV ${item} outListIndexValue )
		install( FILES ${outListIndexValue} DESTINATION "${dest_dir_path}/${baseName}" )
	endforeach( )
endfunction( )

## 拷贝文件或目录到指定目录
## is_replace : 是否替换
## source_home_path : 拷贝文件的根目录
## source_target_path : 拷贝的文件，相对于 source_home_path 目录的文件
## dest_target_path : 目录放置目录
function( copy_file is_replace source_home_path source_target_path dest_target_path )
	if( EXISTS "${source_target_path}" )
		if( IS_DIRECTORY "${source_target_path}" )
			file( GLOB children "${source_target_path}/*" )
			get_current_dir_name( resulut_base_name "${source_target_path}" )
			foreach( child ${children} )
				copy_file( ${is_replace} ${source_home_path} "${child}" "${dest_target_path}/${resulut_base_name}" )
			endforeach( )
		else( )
			get_current_dir_name( resulut_base_name "${source_target_path}" )
			set( target_file_path ${dest_target_path}/${resulut_base_name} )
			if( EXISTS "${target_file_path}" AND NOT ${is_replace} )
				message( "${target_file_path} 已存在，跳过拷贝任务：${target_file_path}" )
				return( )
			endif( )
			set( message_string_key "拷贝" )
			if( ${is_replace} )
				set( message_string_key "覆盖" )
				file( REMOVE_RECURSE ${target_file_path} )
			endif( )
			
			message( "执行${message_string_key}任务：${source_target_path} ${message_string_key}到: ${target_file_path}" )
			
			file( COPY "${source_target_path}" DESTINATION "${dest_target_path}/" )
		endif( )
	else( )
		message( "路径 ${source_target_path} 不存在，拷贝命令失效" )
	endif( )
endfunction( )

# # 拷贝单个路径或文件到指定目标，并且指定是否替换
function( copy_replace_dir_path_cmake_file_command source_path target_path is_replace )
	copy_file( ${is_replace} "${source_path}" "${source_path}" "${target_path}" )
endfunction( )

# # 拷贝多个路径或文件到指定目标，并且指定是否替换
function( copy_replace_mul_dir_path_cmake_file_command is_replace target_path source_path )
	foreach( unity ${${source_path}} )
		copy_replace_dir_path_cmake_file_command( ${unity} ${target_path} ${is_replace} )
	endforeach( )
endfunction( )

# # 拷贝单个路径或文件到指定目标
function( copy_dir_path_cmake_file_command source_path target_path )
	copy_file( FALSE "${source_path}" "${source_path}" "${target_path}" )
endfunction( )

# # 拷贝多个路径或文件到指定目标
function( copy_mul_dir_path_cmake_file_command target_path source_path )
	foreach( unity ${${source_path}} )
		copy_dir_path_cmake_file_command( ${unity} ${target_path} )
	endforeach( )
endfunction( )

# # 拷贝目录到指定路径
function( copy_dir_path_cmake_add_custom_command_POST_BUILD_command builder_target copy_dir_target paste_dir_target )
	get_filename_component( result_abs_path "${copy_dir_target}" ABSOLUTE ) # 全路径
	
	if( EXISTS "${result_abs_path}" )
		add_custom_command(
			TARGET "${builder_target}" POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E echo "执行拷贝任务：${result_abs_path} 拷贝到: ${paste_dir_target}"
			COMMAND ${CMAKE_COMMAND} -E copy_directory "${result_abs_path}/" "${paste_dir_target}"
		)
	else( )
		add_custom_command(
			TARGET "${builder_target}" POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E echo "执行任务：${result_abs_path} 拷贝到: ${paste_dir_target} (失败 ! 路径不存在)"
		)
	endif( )
endfunction( )

# # 拷贝目录到指定路径
function( copy_dir_path_cmake_add_custom_command_PRE_BUILD_command builder_target copy_dir_target paste_dir_target )
	get_absolute_path( result_abs_path ${source_path} )
	
	if( EXISTS ${source_path} )
		add_custom_command(
			TARGET ${builder_target} PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E echo "执行拷贝任务：${result_abs_path} 拷贝到: ${paste_dir_target}"
			COMMAND ${CMAKE_COMMAND} -E copy_directory "${result_abs_path}/" "${paste_dir_target}"
		)
	else( )
		add_custom_command(
			TARGET ${builder_target} PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E echo "执行拷贝任务：${result_abs_path} 拷贝到: ${paste_dir_target}"
		)
	endif( )
endfunction( )

# # 拷贝目录到指定路径
function( copy_dir_path_cmake_add_custom_command_PRE_LINK_command builder_target copy_dir_target paste_dir_target )
	get_absolute_path( result_abs_path ${source_path} )
	
	if( EXISTS ${source_path} )
		add_custom_command(
			TARGET ${builder_target} PRE_LINK
			COMMAND ${CMAKE_COMMAND} -E echo "执行拷贝任务：${result_abs_path} 拷贝到: ${paste_dir_target}"
			COMMAND ${CMAKE_COMMAND} -E copy_directory "${result_abs_path}/" "${paste_dir_target}"
		)
	else( )
		add_custom_command(
			TARGET ${builder_target} PRE_LINK
			COMMAND ${CMAKE_COMMAND} -E echo "执行拷贝任务：${result_abs_path} 拷贝到: ${paste_dir_target}"
		)
	endif( )
endfunction( )

# # 过滤重复路径
function( filter_path_repetition result_list path_dir_s )
	set( exis_dir_path_s ) # 保存已经加载的列表
	
	foreach( out_dir ${${path_dir_s}} )
		set( load_project_path TRUE ) # 是否存在
		get_filename_component( absolutePath "${out_dir}" ABSOLUTE ) # 全路径
		
		foreach( check_exis_path ${exis_dir_path_s} )
			if( ${check_exis_path} STREQUAL ${absolutePath} )
				set( load_project_path FALSE ) # 是否存在
				break( )
			endif( )
		endforeach( )
		
		if( ${load_project_path} ) # # 校验可以加载即可
			list( APPEND exis_dir_path_s ${absolutePath} )
		endif( )
	endforeach( )
	
	set( ${result_list} ${exis_dir_path_s} PARENT_SCOPE )
endfunction( )

# # 返回模板根目录
function( get_temp_file_dir_path result_dir_path )
	get_filename_component( absolutePath "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../temp/" ABSOLUTE ) # 全路径
	set( ${result_dir_path} "${absolutePath}/" PARENT_SCOPE )
endfunction( )

# # 返回路径分隔符
function( get_cmake_separator result_path_sep )
	get_filename_component( absolutePath "${CMAKE_CURRENT_FUNCTION_LIST_DIR}" ABSOLUTE ) # 全路径
	get_filename_component( absoluteParentPath "${CMAKE_CURRENT_FUNCTION_LIST_DIR}" NAME ) # 父路径
	string( LENGTH ${absoluteParentPath} fileNameLen )
	string( LENGTH ${absolutePath} absoluteFileNameLen )
	math( EXPR beginIndex "${absoluteFileNameLen}-${fileNameLen}" OUTPUT_FORMAT DECIMAL )
	string( SUBSTRING ${absolutePath} 0 ${beginIndex} resultSubString )
	math( EXPR satrtIndex "${beginIndex}-1" OUTPUT_FORMAT DECIMAL )
	string( SUBSTRING ${absolutePath} ${satrtIndex} 1 resultSep )
	set( ${result_path_sep} "${resultSep}" PARENT_SCOPE )
endfunction( )

# # 获取所有文件
function( get_path_files result_file_list get_path )
	set( result_list )
	
	foreach( pathItem ${${result_file_list}} )
		get_filename_component( result_abs_path "${pathItem}" ABSOLUTE ) # 全路径
		
		if( IS_DIRECTORY ${result_abs_path} OR NOT EXISTS ${result_abs_path} )
			continue( )
		endif( )
		
		list( FIND result_list ${result_abs_path} find_index )
		
		if( find_index EQUAL -1 ) # # 找不到重复，则加入路径
			list( APPEND result_list ${result_abs_path} )
		endif( )
	endforeach( )
	
	if( IS_DIRECTORY ${get_path} )
		file( GLOB file_get_current_path "${get_path}/*" )
		
		foreach( pathItem ${file_get_current_path} )
			get_filename_component( result_abs_path "${pathItem}" ABSOLUTE ) # 全路径
			get_path_files( foreach_call_result ${result_abs_path} )
			
			foreach( findItem ${foreach_call_result} )
				list( FIND result_list ${findItem} find_index )
				
				if( find_index EQUAL -1 ) # # 找不到重复，则加入路径
					list( APPEND result_list ${findItem} )
				endif( )
			endforeach( )
		endforeach( )
	else( )
		if( EXISTS ${result_abs_path} )
			get_filename_component( result_abs_path "${get_path}" ABSOLUTE ) # 全路径
			list( APPEND result_list ${result_abs_path} )
		endif( )
	endif( )
	
	set( ${result_file_list} ${result_list} PARENT_SCOPE )
endfunction( )

# # 获取所有文件夹
function( get_path_dirs result_dir_list get_path )
	set( result_list )
	
	foreach( pathItem ${${result_dir_list}} )
		get_filename_component( result_abs_path "${pathItem}" ABSOLUTE ) # 全路径
		
		if( NOT EXISTS ${result_abs_path} )
			continue( )
		endif( )
		
		list( FIND result_list ${result_abs_path} find_index )
		
		if( IS_DIRECTORY ${result_abs_path} )
			if( find_index EQUAL -1 ) # # 找不到重复，则加入路径
				list( APPEND result_list ${result_abs_path} )
			endif( )
		endif( )
	endforeach( )
	
	if( IS_DIRECTORY ${get_path} AND EXISTS ${get_path} )
		file( GLOB file_get_current_path "${get_path}/*" )
		
		foreach( pathItem ${file_get_current_path} )
			if( IS_DIRECTORY ${pathItem} )
				get_filename_component( result_abs_path "${pathItem}" ABSOLUTE ) # 全路径
				list( APPEND result_list ${result_abs_path} )
				get_path_dirs( foreach_call_result ${result_abs_path} )
				
				foreach( findItem ${foreach_call_result} )
					list( FIND result_list ${findItem} find_index )
					
					if( find_index EQUAL -1 ) # # 找不到重复，则加入路径
						list( APPEND result_list ${findItem} )
					endif( )
				endforeach( )
			endif( )
		endforeach( )
	endif( )
	
	set( ${result_dir_list} ${result_list} PARENT_SCOPE )
endfunction( )

# # 获取路径作为项目名称
# # 后缀参数作为下标 - get_current_path_name_to_project_name( result_name -4 -3 -2 )
# # - 获取当前路径的 最后 第四个-第三个-第二个 作为合法名称返回
function( get_current_path_name_to_project_name _result_project_name )
	get_filename_component( absFilePath "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE )
	get_cmake_separator( cmake_sep_char_ )
	string_splite( result_list ${absFilePath} ${cmake_sep_char_} )
	list( GET result_list ${ARGN} resultList )
	string( JOIN " " jionResult ${resultList} )
	normal_project_name( result_name "${jionResult}" )
	set( ${_result_project_name} ${result_name} PARENT_SCOPE ) # 返回
endfunction( )

# ## 在目录中查找目录，并且在目标目录中找到 file_name 的文件名
# ## 若存在，则返回所在目录的路径
# ## 文件名不区分大小写
function( find_file_name _out_list check_path_dir file_name )
	set( for_each_list_dirs ${${_out_list}} )
	
	if( IS_DIRECTORY "${check_path_dir}" AND EXISTS "${check_path_dir}" )
		get_path_dirs( dirs_ "${check_path_dir}" )
		
		foreach( current_path_file ${dirs_} )
			set( checkPath "${current_path_file}/${file_name}" )
			
			if( EXISTS "${checkPath}" )
				get_filename_component( absPath "${current_path_file}" ABSOLUTE )
				list( APPEND for_each_list_dirs "${absPath}" )
			endif( )
		endforeach( )
		
		filter_path_repetition( list_result for_each_list_dirs )
		set( ${_out_list} ${list_result} PARENT_SCOPE )
	endif( )
endfunction( )

# # 把 target_obj 目标中的生成文件拷贝到 target_path 目录下
function( copy_target_builder_file_to_path target_obj target_path )
	add_custom_command( TARGET "${target_obj}"
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E echo "执行拷贝任务：$<TARGET_FILE:${result_name}> 拷贝到: ${target_path}/$<TARGET_FILE_NAME:${result_name}>"
		COMMAND ${CMAKE_COMMAND} -E copy -t "${target_path}/" "$<TARGET_FILE:${result_name}>"
		COMMENT "拷贝 $<TARGET_FILE:${target_obj}> 到 ${target_obj_buider_path}"
		DEPENDS "${result_name}"
	)
endfunction( )

# # 取消显示包含头文件内容
function( un_show_include_info target_name )
	# 关闭 /showIncludes
	if( MSVC )
		message( STATUS "使用 MSVC 编译环境" )
		
		
		# 检查是否存在编译选项
		if( CMAKE_DEPFILE_FLAGS_CXX )
			# 移除 /showIncludes 编译选项
			list( REMOVE_ITEM CMAKE_DEPFILE_FLAGS_CXX "/showIncludes" )
			string( REPLACE "/showIncludes" "" CMAKE_DEPFILE_FLAGS_CXX
				"${CMAKE_DEPFILE_FLAGS_CXX}" )
			set( CMAKE_DEPFILE_FLAGS_CXX ${CMAKE_DEPFILE_FLAGS_CXX} PARENT_SCOPE )
		endif( )
		
		# 检查是否存在编译选项
		if( CMAKE_DEPFILE_FLAGS_C )
			# 移除 /showIncludes 编译选项
			list( REMOVE_ITEM CMAKE_DEPFILE_FLAGS_C "/showIncludes" )
			string( REPLACE "/showIncludes" "" CMAKE_DEPFILE_FLAGS_C
				"${CMAKE_DEPFILE_FLAGS_C}" )
			set( CMAKE_DEPFILE_FLAGS_C ${CMAKE_DEPFILE_FLAGS_C} PARENT_SCOPE )
		endif( )
		
		# 获取目标的当前编译选项
		get_target_property( TARGET_COMPILE_OPTIONS ${target_name} COMPILE_OPTIONS )
		
		# 检查是否存在编译选项
		if( TARGET_COMPILE_OPTIONS )
			# 移除 /showIncludes 编译选项
			list( REMOVE_ITEM TARGET_COMPILE_OPTIONS "/showIncludes" )
			
			# 更新目标的编译选项
			set_target_properties( ${target_name} PROPERTIES COMPILE_OPTIONS "${TARGET_COMPILE_OPTIONS}" )
		endif( )
		
		# 检查是否存在编译选项
		if( CMAKE_CXX_SCANDEP_SOURCE )
			# 移除 /showIncludes 编译选项
			list( REMOVE_ITEM CMAKE_CXX_SCANDEP_SOURCE "/showIncludes" )
			list( REMOVE_ITEM CMAKE_CXX_SCANDEP_SOURCE "-showIncludes" )
			string( REPLACE "/showIncludes" "" CMAKE_CXX_SCANDEP_SOURCE
				"${CMAKE_CXX_SCANDEP_SOURCE}" )
			string( REPLACE "-showIncludes" "" CMAKE_CXX_SCANDEP_SOURCE
				"${CMAKE_CXX_SCANDEP_SOURCE}" )
			set( CMAKE_CXX_SCANDEP_SOURCE ${CMAKE_CXX_SCANDEP_SOURCE} PARENT_SCOPE )
		endif( )
		
	endif( )
endfunction( un_show_include_info )

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
