#ifndef CMAKE_TO_C_CPP_HEADER_ENV_H_H_HEAD__FILE__
#define CMAKE_TO_C_CPP_HEADER_ENV_H_H_HEAD__FILE__


#define Builder_Tools_Clang ${Builder_Tools_Clang} // 使用 clang 编译器
#define Builder_Tools_GNU ${Builder_Tools_GNU} // 使用 gnu 编译器
#define Builder_Tools_MSVC ${Builder_Tools_MSVC} // 使用 msvc 编译器
#define Cmake_sep "${_cmake_sep_char}" // cmake 目录分隔符

#define Cmake_Project_Name "${PROJECT_NAME}" // cmake 项目名称
#define Project_Run_bin "${Project_Run_bin}" // cmake 运行目录
#define Project_Plug_bin "${Project_Plug_bin}" // cmake 插件目录
#define Cmake_Source_Dir "${CMAKE_SOURCE_DIR}" // cmake 根目录
#define Archive_Output_Name "${ARCHIVE_OUTPUT_NAME}" // cmake 输出名称
#define Compile_Pdb_Name "${COMPILE_PDB_NAME}" // cmake pbd 名称
#define Compile_SOURCES "${SOURCES}" // 源码
#define user_configure_path "${user_configure_path}" // cmake 配置路径
#define cmake_all_target_obj_config_list "${cmake_all_target_obj_config_list}" // cmake 使用配置的列表
#define current_target_obj "${target_obj}" // cmake 当前配置的项目名称


#define CMAKE_CXX_SOURCE_FILE_EXTENSIONS "${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}" // cmake 当前配置的 C++ 扩展名
#define CMAKE_C_SOURCE_FILE_EXTENSIONS "${CMAKE_C_SOURCE_FILE_EXTENSIONS}" // cmake 当前配置的 C 扩展名
#define LANGUAGE "${LANGUAGE}" // cmake 当前配置的项目语言
#define CMAKE_PROJECT_VERSION "${CMAKE_PROJECT_VERSION}" // cmake 项目版本
#define PROJECT_BINARY_DIR "${PROJECT_BINARY_DIR}" // cmake 项目二进制目录
#define PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}" // cmake 项目源码目录
#define cmake_supper_language_list "${_cmake_supper_language_list}" // cmake 当前配置的项目语言
#endif // CMAKE_TO_C_CPP_HEADER_ENV_H_H_HEAD__FILE__
