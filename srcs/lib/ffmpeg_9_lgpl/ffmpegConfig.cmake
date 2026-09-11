#[[
导入该模块:
	# # 加载 ffmpeg 9.0 lgpl 模块 ffmpeg_9_lgpl 变量为该文件所在目录
	find_package( ffmpeg REQUIRED PATHS "${ffmpeg_9_lgpl}" )
使用说明：
	1.链接项目：
		link_ffmpeg_lib_to_target( 目标 )
	2.拷贝dll到 exe 目标
		copy_ffmpeg_dll_to_target( 目录 )

]]



cmake_minimum_required( VERSION 3.19 )

### 拷贝 dll
function( copy_ffmpeg_dll_to_target copy_dir_path )
	set( dll_dir "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/bin" )
	file( GLOB dll_file_list "${dll_dir}/*.dll" )
	
	foreach( src ${dll_file_list} )
		get_filename_component( filename "${src}" NAME )
		set( dst "${copy_dir_path}/${filename}" )
		if( NOT EXISTS "${dst}" )
			file( COPY ${src} DESTINATION "${copy_dir_path}" )
		endif( )
	endforeach( )
	
endfunction( )

### 链接库
function( link_ffmpeg_lib_to_target target )
	target_include_directories( "${target}" PRIVATE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/include" )
	set( lib_dir "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/lib" )
	file( GLOB lib_files "${lib_dir}/*.lib" )
	target_link_libraries( "${target}" PRIVATE ${lib_files} )
endfunction( )

message( "-------------------------" )
message( "加载 ffmpeg 9 lgpl 模块完毕" )
message( "-------------------------" )
