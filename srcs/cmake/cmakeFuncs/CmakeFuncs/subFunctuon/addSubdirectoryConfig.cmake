cmake_minimum_required( VERSION 3.19 )

# # 检测列表是否已经被定义，不被定义返回 FALSE
# # result_ 返回值
# # _CHECK_CMAKE_VALUE_ 检测列表，允许多个
function( check_value_is_define result_ )
    set( OPTIONAL )
    set( oneValueArgs )
    set( multiValueArgs _CHECK_CMAKE_VALUE_ )
    cmake_parse_arguments( PARSE_ARGV 1 arg "${options}" "${oneValueArgs}" "${multiValueArgs}" )
    set( error_list )

    foreach( item ${arg__CHECK_CMAKE_VALUE_} )
        if( DEFINED item AND ${item} )
            continue()
        endif()

        list( APPEND error_list ${item} )
    endforeach()

    list( LENGTH error_list len )

    if( len EQUAL 0 )
        unset( ${result_} PARENT_SCOPE )
    else()
        set( ${result_} ${error_list} PARENT_SCOPE )
    endif()
endfunction()


# # 添加支持语言
function( supper_cmake_builder_language result_language_list_ )
    check_language( Fortran )
    set( supper_language_list )

    if( CMAKE_Fortran_COMPILER )
        enable_language( Fortran )
        list( APPEND supper_language_list "Fortran" )
    endif()

    check_language( CXX )

    if( CMAKE_CXX_COMPILER )
        enable_language( CXX )
        list( APPEND supper_language_list "CXX" )
    endif()

    check_language( C )

    if( CMAKE_C_COMPILER )
        enable_language( C )
        list( APPEND supper_language_list "C" )
    endif()

    check_language( ASM )

    if( CMAKE_ASM_COMPILER )
        enable_language( ASM )
        list( APPEND supper_language_list "ASM" )
    endif()

    check_language( ASM_NASM )

    if( CMAKE_ASM_NASM_COMPILER )
        enable_language( ASM_NASM )
        list( APPEND supper_language_list "ASM_NASM" )
    endif()

    check_language( ASM_MARMASM )

    if( CMAKE_ASM_MARMASM_COMPILER )
        enable_language( ASM_MARMASM )
        list( APPEND supper_language_list "ASM_MARMASM" )
    endif()

    check_language( ASM_MASM )

    if( CMAKE_ASM_MASM_COMPILER )
        enable_language( ASM_MASM )
        list( APPEND supper_language_list "ASM_MASM" )
    endif()

    check_language( ASM-ATT )

    if( CMAKE_ASM-ATT_COMPILER )
        enable_language( ASM-ATT )
        list( APPEND supper_language_list "ASM-ATT" )
    endif()

    check_language( Swift )

    if( CMAKE_Swift_COMPILER )
        enable_language( Swift )
        list( APPEND supper_language_list "Swift" )
    endif()

    check_language( CSharp )

    if( CMAKE_CSharp_COMPILER )
        enable_language( CSharp )
        list( APPEND supper_language_list "CSharp" )
    endif()

    check_language( CUDA )

    if( CMAKE_CUDA_COMPILER )
        enable_language( CUDA )
        list( APPEND supper_language_list "CUDA" )
    endif()

    check_language( HIP )

    if( CMAKE_HIP_COMPILER )
        enable_language( HIP )
        list( APPEND supper_language_list "HIP" )
    endif()

    check_language( ISPC )

    if( CMAKE_ISPC_COMPILER )
        enable_language( ISPC )
        list( APPEND supper_language_list "ISPC" )
    endif()

    message( "================== 支持语言\n\t\t ${supper_language_list}\n==================" )
    set( ${result_language_list_} ${supper_language_list} PARENT_SCOPE )
endfunction()

# # 添加指定开发环境的源码后缀
# # extension_list : 指定后缀
# # LANGUAGES args :  语言列表
# # SUFFIXS arg s: 后缀列表
function( append_source_file_extensions extension_list )
    if( NOT PROJECT_NAME )
        message( FATAL_ERROR "需要先配置项目，否则该能容无法使用" )
        return()
    endif()

    set( OPTIONAL )
    set( oneValueArgs )
    set( multiValueArgs LANGUAGES SUFFIXS )
    cmake_parse_arguments( PARSE_ARGV 0 arg "${options}" "${oneValueArgs}" "${multiValueArgs}" )

    foreach( language ${arg_LANGUAGES} )
        check_language( ${language} )

        if( NOT CMAKE_${language}_COMPILER )
            message( "不支持 ${language} 开发环境，请重新检查" )
            continue()
        endif()

        message( "================== 当前后缀 ${language}" )

        foreach( extension ${arg_SUFFIXS} )
            list( APPEND CMAKE_${language}_SOURCE_FILE_EXTENSIONS "${extension}" )
        endforeach()

        set( CMAKE_${language}_SOURCE_FILE_EXTENSIONS ${CMAKE_${language}_SOURCE_FILE_EXTENSIONS} PARENT_SCOPE )

        message( "\t\tCMAKE_${language}_SOURCE_FILE_EXTENSIONS=${CMAKE_${language}_SOURCE_FILE_EXTENSIONS}" )
        message( "==================" )
    endforeach()
endfunction()

# # 添加 C CPP 后缀
macro( append_CXX_C_source_file_extensions extension_list )
    if( NOT PROJECT_NAME )
        message( FATAL_ERROR "需要先配置项目，否则该能容无法使用" )
        return()
    endif()

    check_language( C )
    check_language( CXX )

    if( NOT CMAKE_CXX_COMPILER AND NOT CMAKE_C_COMPILER )
        message( "\t\t!!! 当前 cmake 环境并不支持 C/C++ ，请重新检查开发环境" )
        return()
    endif()

    foreach( extension ${ARGV} )
        if( CMAKE_CXX_COMPILER )
            list( APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS "${extension}" )
        endif()

        if( CMAKE_C_COMPILER )
            list( APPEND CMAKE_C_SOURCE_FILE_EXTENSIONS "${extension}" )
        endif()
    endforeach()

    message( "================== 当前后缀" )

    if( CMAKE_CXX_COMPILER )
        message( "\t\tCMAKE_CXX_SOURCE_FILE_EXTENSIONS=${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}" )
    endif()

    if( CMAKE_C_COMPILER )
        message( "\t\tCMAKE_C_SOURCE_FILE_EXTENSIONS=${CMAKE_C_SOURCE_FILE_EXTENSIONS}" )
    endif()

    message( "==================" )
endmacro()

# ## 把工具库加入 cmake 项目内
function( add_subdirectory_tools_lib )
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../userLib/tools" )
    append_sub_directory_cmake_project_path_list( root_path )
endfunction()


# ## 把测试库加入 cmake 项目内
function( add_subdirectory_code_learn_project )
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../cmake_source/learn" )
    get_path_cmake_dir_path( lib_list "${root_path}" "CMakeLists.txt" )
    filter_path_repetition( list_result lib_list )
    append_sub_directory_cmake_project_path_list( list_result )
endfunction()

# ## 把 imgui 学习案例加入 cmake 项目内
function( add_subdirectory_code_imgui_project )
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../cmake_source/learn/imgui" )
    get_path_cmake_dir_path( lib_list "${root_path}" "CMakeLists.txt" )
    filter_path_repetition( list_result lib_list )
    append_sub_directory_cmake_project_path_list( list_result )
endfunction()

# ## 把 qt 学习案例加入 cmake 项目内
function( add_subdirectory_code_qt_project )
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../cmake_source/learn/qt" )
    get_path_cmake_dir_path( lib_list "${root_path}" "CMakeLists.txt" )
    filter_path_repetition( list_result lib_list )
    append_sub_directory_cmake_project_path_list( list_result )
endfunction()


# ## 把 cpp 23 学习案例加入 cmake 项目内
function( add_subdirectory_code_cpp23_project )
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../cmake_source/learn/cpp 23" )
    get_path_cmake_dir_path( lib_list "${root_path}" "CMakeLists.txt" )
    filter_path_repetition( list_result lib_list )
    append_sub_directory_cmake_project_path_list( list_result )
endfunction()

# ## 把 opengl 学习案例加入 cmake 项目内
function( add_subdirectory_code_opengl_project )
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../cmake_source/learn/opengl" )
    get_path_cmake_dir_path( lib_list "${root_path}" "CMakeLists.txt" )
    filter_path_repetition( list_result lib_list )
    append_sub_directory_cmake_project_path_list( list_result )
endfunction()

# ## 把 cmake 学习案例加入 cmake 项目内
function( add_subdirectory_code_cmake_project )
    set( root_path "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../../cmake_source/learn/cmake" )
    get_path_cmake_dir_path( lib_list "${root_path}" "CMakeLists.txt" )
    filter_path_repetition( list_result lib_list )
    append_sub_directory_cmake_project_path_list( list_result )
endfunction()

# # 追加路径到项目列表，同时校验去除参数当中重复的路径
function( append_sub_directory_cmake_project_path_s path_dir_s )
    # 获取列表
    get_in_cmakeFunction_call_load_sub_directory_project_list( _load_list )

    foreach( out_dir ${path_dir_s} )
        get_filename_component( absolutePath "${out_dir}" ABSOLUTE ) # 全路径
        list( FIND _load_list "${absolutePath}" index )

        if( index EQUAL -1 AND IS_DIRECTORY "${absolutePath}" AND EXISTS "${absolutePath}" )
            message( STATUS "正在添加路径 :\t" "${absolutePath}" )
            add_subdirectory( "${absolutePath}" )
            list( APPEND _load_list "${absolutePath}" )
        endif()
    endforeach()

    # 重新配置列表
    set( property_name "addend_sub_directory_list_property" )
    get_property( _my_addend_sub_directory_list_is_define GLOBAL PROPERTY "${property_name}" DEFINED )

    if( _my_addend_sub_directory_list_is_define )
        set_property( GLOBAL PROPERTY "${property_name}" ${_load_list} )
    else()
        define_property( GLOBAL PROPERTY "${property_name}" )
        set_property( GLOBAL PROPERTY "${property_name}" ${_load_list} )
    endif()
endfunction()

# # 追加路径到项目列表，同时校验去除参数当中重复的路径
function( append_sub_directory_cmake_project_path_list path_dir_s )
    # 获取列表
    get_in_cmakeFunction_call_load_sub_directory_project_list( _load_list )

    foreach( out_dir ${${path_dir_s}} )
        get_filename_component( absolutePath "${out_dir}" ABSOLUTE ) # 全路径
        list( FIND _load_list "${absolutePath}" index )

        if( index EQUAL -1 AND IS_DIRECTORY "${absolutePath}" AND EXISTS "${absolutePath}" )
            message( STATUS "正在添加路径 :\t" "${absolutePath}" )
            add_subdirectory( "${absolutePath}" )
            list( APPEND _load_list "${absolutePath}" )
        endif()
    endforeach()

    # 重新配置列表
    set( property_name "get_in_cmakeFunction_call_load_sub_directory_project_list" )
    get_property( _my_addend_sub_directory_list_is_define GLOBAL PROPERTY "${property_name}" DEFINED )

    if( _my_addend_sub_directory_list_is_define )
        set_property( GLOBAL PROPERTY "${property_name}" ${_load_list} )
    else()
        define_property( GLOBAL PROPERTY "${property_name}" )
        set_property( GLOBAL PROPERTY "${property_name}" ${_load_list} )
    endif()
endfunction()

include( CheckLanguage )

# # 获取使用 append_sub_directory_cmake_project_path 加载子项目列表的项目路径列表
function( get_in_cmakeFunction_call_load_sub_directory_project_list result_list_ )
    set( property_name "get_in_cmakeFunction_call_load_sub_directory_project_list" )
    get_property( _my_addend_sub_directory_list_is_define GLOBAL PROPERTY "${property_name}" DEFINED )

    if( _my_addend_sub_directory_list_is_define )
        get_property( _my_addend_sub_directory_list GLOBAL PROPERTY "${property_name}" )
        set( ${result_list_} ${_my_addend_sub_directory_list} PARENT_SCOPE )
        return()
    endif()

    define_property( GLOBAL PROPERTY "${property_name}" )
endfunction()

get_filename_component( abs "${CMAKE_CURRENT_LIST_FILE}" ABSOLUTE )
string( FIND "${abs}" "${CMAKE_HOME_DIRECTORY}" index )

if( NOT ${index} EQUAL -1 )
    string( LENGTH "${abs}" _orgStrLen )
    string( LENGTH "${CMAKE_HOME_DIRECTORY}" _findStrLen )
    math( EXPR _subLen "${_orgStrLen} - ${_findStrLen}" )
    string( SUBSTRING "${abs}" ${_findStrLen} ${_subLen} abs )
    set( abs ".${abs}" )
endif()

message( "----\n\t\t调用:(${abs}[${CMAKE_CURRENT_FUNCTION}]:${CMAKE_CURRENT_LIST_LINE})行 ->\n\t\t\t消息:列表加载完毕" )
