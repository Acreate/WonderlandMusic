cmake_minimum_required( VERSION 3.19 )


include( CMakeParseArguments )

find_package( addSubdirectory REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/subFunctuon" GLOBAL )
find_package( path REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/subFunctuon" GLOBAL )
find_package( setTargetProperty REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/subFunctuon" GLOBAL )
find_package( string REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/subFunctuon" GLOBAL )
find_package( targetLink REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/subFunctuon" GLOBAL )
find_package( userQt REQUIRED PATHS "${CMAKE_CURRENT_LIST_DIR}/subFunctuon" GLOBAL )

get_filename_component( abs "${CMAKE_CURRENT_LIST_FILE}" ABSOLUTE )
string( FIND "${abs}" "${CMAKE_HOME_DIRECTORY}" index )

if( NOT ${index} EQUAL -1 )
	string( LENGTH "${abs}" _orgStrLen )
	string( LENGTH "${CMAKE_HOME_DIRECTORY}" _findStrLen )
	math( EXPR _subLen "${_orgStrLen} - ${_findStrLen}" )
	string( SUBSTRING "${abs}" ${_findStrLen} ${_subLen} abs )
	set( abs ".${abs}" )
endif( )

function( init_cmake_func )
	set( CMAKE_C_STANDARD 17 PARENT_SCOPE )
	set( CMAKE_C_STANDARD_REQUIRED ON PARENT_SCOPE )
	set( CMAKE_C_VISIBILITY_PRESET hidden PARENT_SCOPE )
	set( CMAKE_C_EXTENSIONS ON PARENT_SCOPE )
	set( CMAKE_CXX_STANDARD 23 PARENT_SCOPE )
	set( CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE )
	set( CMAKE_CXX_VISIBILITY_PRESET hidden PARENT_SCOPE )
	set( CMAKE_CXX_EXTENSIONS ON PARENT_SCOPE )
	set( CMAKE_INCLUDE_CURRENT_DIR ON PARENT_SCOPE )

	set( CMAKE_SUPPRESS_REGENERATION ON PARENT_SCOPE )

endfunction( )

message( "----\n\t\t调用:(${abs}[${CMAKE_CURRENT_FUNCTION}]:${CMAKE_CURRENT_LIST_LINE})行 ->\n\t\t\t消息:列表加载完毕" )
