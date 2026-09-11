cmake_minimum_required( VERSION 3.19 )

# ## 标准化项目名称
function( normal_project_name noormal_name org_name )
    string( REPLACE " " "_" var_replace ${org_name} )
    string( REPLACE "/" "_" var_replace ${var_replace} )
    set( ${noormal_name} ${var_replace} PARENT_SCOPE )
endfunction()

# # 切分字符串
# # result_list 返回切分后的字符串列表
# # src_str 被切分的源字符串
# # target_str 被切分的匹配字符串
function( string_splite result_list src_str target_str )
    if( NOT src_str OR NOT target_str )
        return()
    endif()

    set( spliteResult )
    string( LENGTH ${src_str} _strLen )

    if( _strLen EQUAL 0 )
        return()
    endif()

    while( true )
        string( FIND ${src_str} ${target_str} resultIndex )

        if( ${resultIndex} EQUAL -1 )
            break()
        endif()

        string( SUBSTRING ${src_str} 0 ${resultIndex} subResult )
        list( APPEND spliteResult ${subResult} )
        math( EXPR resultIndex "${resultIndex}+1" OUTPUT_FORMAT DECIMAL )
        string( SUBSTRING ${src_str} ${resultIndex} -1 subResult )

        string( LENGTH ${src_str} _strLen )

        if( _strLen EQUAL 0 )
            break()
        endif()

        set( src_str ${subResult} )
    endwhile()

    list( APPEND spliteResult ${src_str} )
    set( ${result_list} ${spliteResult} PARENT_SCOPE )
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
