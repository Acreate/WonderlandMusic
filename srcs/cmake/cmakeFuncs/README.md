# cmakeFuncsopengl_demo

## 介绍

cmake 功能合集

## cmake 模块函数

### CmakeFuncsConfig.cmake

使用 find_package 功能导入。它自动导入子功能项

```
    1. addSubdirectoryConfig.cmake
    2. pathConfig.cmake
    3. setTargetPropertyConfig.cmake
    4. stringConfig.cmake
    5. targetLinkConfig.cmake
```

```
案例:
	find_package( CmakeFuncs REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/srcs/cmakeFuncs/CmakeFuncs" )
```

#### include_path_package()

加载 pathConfig.cmake

#### include_setTargetProperty_package()

加载 setTargetPropertyConfig.cmake

#### include_string_package()

加载 stringConfig.cmake

#### include_targetLink_package()

加载 targetLinkConfig.cmake

#### include_addSubdirectory_package()

加载 addSubdirectoryConfig.cmake

#### include_everything_package( package_name package_path )

在路径 package_path 下加载 ${package_name}.cmake

### addSubdirectoryConfig.cmake

#### supper_cmake_builder_language( result_language_list_ )

激活并且返回当前环境支持编译环境

```cmake
cmake_minimum_required( VERSION 3.19 )

# # 加载模块
find_package( CmakeFuncs REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/srcs/cmakeFuncs/CmakeFuncs" )

# # 获取当前文件夹名称
get_current_dir_name( prject_name ${CMAKE_CURRENT_SOURCE_DIR} )
message( "============ ${prject_name}" )
message( "name = " ${prject_name} ) # # 当前文件名配置为项目名称
project( ${prject_name} )
message( "============ ${CURRENT_FOLDER}" )

set( CMAKE_C_STANDARD 17 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_VISIBILITY_PRESET hidden )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )

supper_cmake_builder_language( _cmake_supper_language_list ) # # 语言支持列表
```



#### append_CXX_C_source_file_extensions( extension_list )

添加 c 和 cpp 后缀名称

```cmake
cmake_minimum_required( VERSION 3.19 )

## 加载模块
find_package( CmakeFuncs REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/srcs/cmakeFuncs/CmakeFuncs" )

## 获取当前文件夹名称
get_current_dir_name( prject_name ${CMAKE_CURRENT_SOURCE_DIR} )
message( "============ ${prject_name}" )
message( "name = " ${prject_name} ) ## 当前文件名配置为项目名称
project( ${prject_name} )
message( "============ ${CURRENT_FOLDER}" )

set( CMAKE_C_STANDARD 17 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_VISIBILITY_PRESET hidden )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )

append_CXX_C_source_file_extensions( h hpp hc H HPP HC ) ## 追加后缀名
```



#### check_value_is_define( result_ [\__CHECK_CMAKE_VALUE\_\_ <value_name>] )

检查变量列表，标注其中未定义的变量

```cmake
## 检查 Qt6_DIR 与 qt_DIR 是否已经被定义，如果其中一个变量未定义，则返回该字面变量
check_value_is_define( _result _CHECK_CMAKE_VALUE_ Qt6_DIR qt_DIR )
## 若 Qt6_DIR 未定义，则 _result 列表理应保存 Qt6_DIR 名称，而不是 ${Qt6_DIR}
```

#### add_subdirectory_tools_lib()

把工具库加入 cmake 项目内

#### append_sub_directory_cmake_project_path_list( path_dir_s )

把列表当中的所有项目都加入到 cmake 项目内

必须保证该路径存在可用的 CMakeLists.txt 文件

该功能提供更多的工具帮助

path_dir_s 为列表

```cmake
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../userLib/tools" )
    append_sub_directory_cmake_project_path_list( root_path )
```

```cmake
	## 非法操作，请使用 append_sub_directory_cmake_project_path_s( path_dir_s )
	append_sub_directory_cmake_project_path_s( "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../userLib/tools"  )
```



#### append_sub_directory_cmake_project_path_s( path_dir_s )

增加路径列表到项目

path_dir_s 为路径列表，并非数组

```cmake
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../userLib/tools" )
    append_sub_directory_cmake_project_path_s( ${root_path} )
```

```cmake
    append_sub_directory_cmake_project_path_s( "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../userLib/tools"  )
```



#### get_in_cmakeFunction_call_load_sub_directory_project_list( result_list_ )

返回使用 append_sub_directory_cmake_project_path( path_dir_s ) 函数加载的所有目标

### pathConfig.cmake

#### init_std_builder_path()

初始化路径，允许下列变量

\## Project_Run_Bin_Path : 二进制路径

\## Project_Run_Pbd_Path : 调试路径

\## Project_Run_Static_Lib_Path : 静态库目录

\## Project_Install_Path : 安装目录

```cmake
set_target_bin_out_path_property( "${prject_name}" "${Project_Run_Bin_Path}/${prject_name}" )
set_target_static_lib_out_path_property( "${prject_name}" "${Project_Run_Static_Lib_Path}/${prject_name}" )
set_target_pdb_out_path_property( "${prject_name}" "${Project_Run_Pbd_Path}/${prject_name}" )
```

#### copy_replace_dir_path_cmake_file_command( source_path target_path is_replace )

把 source_path  （该文件）拷贝到 target_path 目标，如果存在相同目标，则使用 is_replace 指定是否覆盖

#### copy_replace_mul_dir_path_cmake_file_command(  is_replace target_path source_path  )

把 source_path  (目录中所有文件)拷贝到 target_path 目标，如果存在相同目标，则使用 is_replace 指定是否覆盖

#### copy_target_builder_file_to_path( target_obj target_path )

把 target_obj 目标中的生成文件拷贝到 target_path 目录下

#### get_current_dir_name( out_name in_path )

获取当前文件或文件夹的名称

#### get_parent_dir_name( out_name in_path )

获取父级文件夹名称

#### get_path_cmake_dir_path( out_list check_path_dir file_name )

获取指定路径下的所有匹配文件名

#### get_path_sources( out_file_list  [PATHS <路径 ...>] [LANGUAGES <语言 ...> ] [SUFFIXS <后缀 ...> ])

out_file_list  返回源码列表

PATHS 指定后续参数列表为路径，允许多个

LANGUAGES 从指定开发语言获取源码后缀，允许多个编程语言，可以使用 supper_cmake_builder_language( result_language_list_ ) 获取支持语言

SUFFIXS 指定后续参数列表为追加后缀，允许多个

```cmake
## 检查 "${CMAKE_CURRENT_LIST_DIR}/srcs" 路径当中所有支持 C/C++ 的源码，并且在这之上增加 .e 后缀检查
get_path_sources( project_src_file PATHS "${CMAKE_CURRENT_LIST_DIR}/srcs" LANGUAGES CXX C SUFFIXS ".e" )
```



#### get_path_cxx_and_c_sources( out_file_list check_path )

获取源码，根据 CMAKE_CXX_SOURCE_FILE_EXTENSIONS 与 CMAKE_C_SOURCE_FILE_EXTENSIONS 获取后缀，返回源码

需要支持 C/C++，使用 check_language( C ) 与 check_language( CXX ) 返回 CMAKE_CXX_COMPILER 与 CMAKE_C_COMPILER 定义判定

​	out_file_list 返回源码

​	check_path 检查路径

#### get_path_sources check_path( find_expansion out_file_list )

获取指定后缀的源码

#### user_install_copy_file( dest_dir_path )

使用安装模式拷贝路径

#### copy_dir_path_cmake_file_command( source_path target_path )

生成 cmake 项目名时候拷贝内容

#### copy_dir_path_cmake_add_custom_command_POST_BUILD_command( builder_target copy_dir_target paste_dir_target )

使用 post build 选项拷贝

#### copy_dir_path_cmake_add_custom_command_PRE_BUILD_command( builder_target copy_dir_target paste_dir_target )

使用 pre build 选项拷贝

#### copy_dir_path_cmake_add_custom_command_PRE_LINK_command( builder_target copy_dir_target paste_dir_target )

使用 pre link 选项拷贝

#### filter_path_repetition( result_list path_dir_s )

过滤重复的路径

#### get_temp_file_dir_path( result_dir_path )

返回模板目录

#### get_absolute_path( result_dir_path in_path )

返回绝对目录

#### get_cmake_separator( result_path_sep )

返回路径分隔符

#### get_path_files( result_file_list get_path )

返回该路径下的所有文件

#### get_path_dirs( result_dir_list get_path )

返回该路径下的所有文件夹

#### un_show_include_info()

取消显示包含头文件列表信息

### setTargetPropertyConfig.cmake

#### set_target_BIN_out_path_property( target_obj out_path )

配置目标的可执行文件输出，win当中包含动态库

#### set_target_Static_Lib_out_path_property( target_obj out_path )

配置目标的库输出目标

#### set_target_PDB_out_path_property( target_obj out_path )

配置目标的 pdb 文件输出

#### set_target_WIN32_cmd_windows( target_obj )

配置目标是否使用命令行模式

#### set_target_WIN32_show_windows( target_obj )

配置目标是否使用窗口模式

### stringConfig.cmake

#### normal_project_name( noormal_name org_name )

重新配置名称，并且返回正确名称

#### string_splite( result_list src_str target_str )

切分字符串

### targetLinkConfig.cmake

#### get_target_builder_path( result_out_path target_obj )

获取目标的编译路径

result_out_path : 返回的编译路径

target_obj : 获取目标

#### configure_temp_files( target_path target_obj )

目标配置cmake环境头文件

#### configure_all_target()

目标生成 cmake 头文件。

需要使用 configure_temp_files( target_path target_obj ) 配置路径

并且该项目由 append_sub_directory_cmake_project_path( path_dir_s ) 加载

### qtConfig.cmake

包含 cmake 当中激活qt功能的函数

#### printf_qt_cmake_out()

打印 cmake 当中的 qt 环境变量

#### qt_generate_deploy_cmake_script_inatll_job( _out_deploy_script_job_path target_obj )

激活 qt 安装功能，自动配置 qt 环境所需要的库文件

_out_deploy_script_job_path 返回生成脚本的路径

target_obj 目标名称

```
qt_generate_deploy_cmake_script_inatll_job( scrpt_path_ "${prject_name}" )
```

#### init_qt_dir_event( qt_dir )

激活 qt 环境

该功能优先使用 \${qt_dir} 路径激活 qt 环境，备选使用 \${Qt6_DIR} 

功能只能在未初始化时调用，再次调用，或者 qt 实现 cmake 初始化时成功时，该调用会失败

如果需要重新初始化 qt 的 cmake，可以调用 update_qt_dir_event( qt_dir )

```cmake
init_qt_dir_event( "${Qt6_DIR}" )
```

#### update_qt_dir_event( qt_dir )

更新 qt 的 cmake 环境

与 init_qt_dir_evect( qt_dir ) 不同，该调用会覆盖就配置

该功能优先使用 \${qt_dir} 路径激活 qt 环境，备选使用 \${Qt6_DIR} 

```cmake
update_qt_dir_event( "${Qt6_DIR}" )
```



