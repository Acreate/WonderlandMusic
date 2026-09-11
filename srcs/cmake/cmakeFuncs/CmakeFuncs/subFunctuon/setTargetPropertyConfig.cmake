cmake_minimum_required( VERSION 3.19 )

## 对全局关闭增量编译
## 对于一些特殊环境，应当除去增量编译，否则会导致生成的 .pdb 过大而无法编译。
## 其次，对于 qt 来说，会导致调用 main 等主函数后，调试器会尝试发出异常中断—增量编译导致的符号导向异常或释放异常。
function( close_global_compile_batching )
	# 全局对所有目标生效
	if( MSVC )
		# 禁用最小重新生成（增量编译检测）
		add_compile_options( /Gm- )
		
		# 全配置禁用增量链接 Debug/Release/RelWithDebInfo
		set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL:NO" PARENT_SCOPE )
		set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /INCREMENTAL:NO" PARENT_SCOPE )
		set( CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /INCREMENTAL:NO" PARENT_SCOPE )
		
		# 可选：关闭编译批处理，每次只编译一个cpp
		set( CMAKE_VS_NO_COMPILE_BATCHING ON PARENT_SCOPE )
	endif( )
endfunction( )


## 对目标关闭增量编译
function( close_target_compile_batching target )
	if( MSVC )
		target_compile_options( ${target} PRIVATE /Gm- )
		target_link_options( ${target} PRIVATE /INCREMENTAL:NO )
		set_target_properties( ${target} PROPERTIES VS_NO_COMPILE_BATCHING ON )
	endif( )
endfunction( )


# ## 设置程序输出名称
function( set_target_BIN_out_name_property target_obj out_name )
	set_target_properties( "${target_obj}" PROPERTIES
		DEBUG_OUTPUT_NAME "${out_name}"
		RELEASE_OUTPUT_NAME "${out_name}"
		OUTPUT_NAME "${out_name}"
	)
endfunction( )
# ## 设置程序输出位置
function( set_target_BIN_out_path_property target_obj out_path )
	set_target_properties( "${target_obj}" PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${out_path}"
		RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${out_path}"
		RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${out_path}"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${out_path}"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${out_path}
	)
endfunction( )

# ## 设置静态库输出位置
function( set_target_Static_Lib_out_path_property target_obj out_path )
	set_target_properties( "${target_obj}" PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${out_path}"
		LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${out_path}"
		LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${out_path}"
		LIBRARY_OUTPUT_DIRECTORY_RELEASE "${out_path}"
		LIBRARY_OUTPUT_DIRECTORY_DEBUG "${out_path}"

		ARCHIVE_OUTPUT_DIRECTORY "${out_path}"
		ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${out_path}"
		ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${out_path}"
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${out_path}"
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${out_path}"
	)
endfunction( )

# ## 设置 pbd 输出位置
function( set_target_PDB_out_path_property target_obj out_path )
	set_target_properties( "${target_obj}" PROPERTIES
		PDB_OUTPUT_DIRECTORY "${out_path}"
		PDB_OUTPUT_DIRECTORY_MINSIZEREL "${out_path}"
		PDB_OUTPUT_DIRECTORY_RELWITHDEBINFO "${out_path}"
		PDB_OUTPUT_DIRECTORY_RELEASE "${out_path}"
		PDB_OUTPUT_DIRECTORY_DEBUG "${out_path}"
	)
	set_target_properties( "${target_obj}" PROPERTIES
		COMPILE_PDB_OUTPUT_DIRECTORY "${out_path}"
		COMPILE_PDB_OUTPUT_DIRECTORY_MINSIZEREL "${out_path}"
		COMPILE_PDB_OUTPUT_DIRECTORY_RELWITHDEBINFO "${out_path}"
		COMPILE_PDB_OUTPUT_DIRECTORY_RELEASE "${out_path}"
		COMPILE_PDB_OUTPUT_DIRECTORY_DEBUG "${out_path}"
	)
	set( pbd_file_path "${out_path}/${target_obj}.pdb" )
	if( EXISTS "${pbd_file_path}" )
		file( SIZE ${pbd_file_path} file_bytes )
		math( EXPR file_mb "${file_bytes} / 1048576" )
		if( ${file_mb} GREATER 1024 )
			file( REMOVE "${pbd_file_path}" )
		endif( )
	endif( )
endfunction( )

# ## 激活 pbd 的输出
function( enable_target_PDB_propertie target_obj )
	set_target_properties( "${target_obj}" PROPERTIES
		CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi"
		CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG /OPT:REF /OPT:ICF"
		CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEBUG /OPT:REF /OPT:ICF"
	)
endfunction( )

# ## 取消 pbd 的输出
function( cancel_target_PDB_propertie target_obj )
	# 仅针对 MSVC 编译器（Windows 平台）生效
	if( MSVC )
		# 1. 关闭 C/C++ 编译阶段的调试信息生成
		# /Z7、/Zi、/ZI 是生成调试信息的编译选项，/Zc:inline- 避免额外符号生成
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Z7- /Zi- /ZI- /Zc:inline-" )
		set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Z7- /Zi- /ZI- /Zc:inline-" )
		
		# 2. 关闭链接器阶段的调试信息生成
		# /DEBUG 是生成 .pdb 的核心链接选项，/DEBUG:NO 显式禁用
		set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG:NO" )
		set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEBUG:NO" )
		set( CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} /DEBUG:NO" )
		
		# 3. 可选：Release 模式下进一步禁用所有调试相关选项（强化版）
		if( CMAKE_BUILD_TYPE STREQUAL "Release" )
			set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Od- /Oy /GS-" )
			set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Od- /Oy /GS-" )
		endif( )
	endif( )
endfunction( )

# ## 独立 pbd 的输出
function( target_obj_PDB_propertie target_obj )
	# 仅针对 MSVC 编译器（Windows 平台）生效
	if( MSVC )
		get_target_property( targetPDBOutPath "${target_obj}" PDB_OUTPUT_DIRECTORY
		)
		get_target_property( targetSources ${target_obj} SOURCES )
		set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /FS" )
		set( CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /INCREMENTAL:NO" )
		
		# 遍历每个源文件，为其指定专属 PDB
		foreach( SRC_FILE ${targetSources} )
			# 获取源文件的文件名（不含路径和后缀），作为 PDB 名称
			get_filename_component( FILE_NAME ${SRC_FILE} NAME_WE )
			
			# 为该源文件添加编译选项：/Fd + 专属 PDB 名
			set_source_files_properties( ${SRC_FILE} PROPERTIES
				COMPILE_OPTIONS $<$<CONFIG:Debug>:/Fd${targetPDBOutPath}/${FILE_NAME}.pdb>
			)
		endforeach( )
	endif( )
endfunction( )

# ## 设置程序为命令行窗口
function( set_target_WIN32_cmd_windows target_obj )
	if( WIN32 )
		set_target_properties( "${target_obj}" PROPERTIES WIN32_EXECUTABLE FALSE )
	endif( )
endfunction( )

# ## 设置程序为窗口
function( set_target_WIN32_show_windows target_obj )
	if( WIN32 )
		set_target_properties( "${target_obj}" PROPERTIES WIN32_EXECUTABLE TRUE )
	endif( )
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
