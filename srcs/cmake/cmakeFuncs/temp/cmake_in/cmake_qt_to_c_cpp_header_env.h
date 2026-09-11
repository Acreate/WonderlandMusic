#ifndef CMAKE__QT_TO_C_CPP_HEADER_ENV_H_H_HEAD__FILE__
#define CMAKE__QT_TO_C_CPP_HEADER_ENV_H_H_HEAD__FILE__

/// @brief qt cmake 目录
#define CMAKE_Qt6_DIR "${Qt6_DIR}" 
/// @brief qt cmake 目录
#define CMAKE_Qt_DIR "${Qt_DIR}" 
/// @brief qt 主版本号
#define CMAKE_QT_VERSION_MAJOR "${QT_VERSION_MAJOR}" 
/// @brief qt 版本
#define CMAKE_QT_VERSION "${QT_VERSION}" 
/// @brief qt 工具目录
#define CMAKE_DEPLOY_QT_HOME "${DEPLOY_QT_HOME}" 
/// @brief qmake 路径
#define CMAKE_QT_QMAKE_EXECUTABLE "${QT_QMAKE_EXECUTABLE}" 
/// @brief qt core 工具 cmake
#define CMAKE_Qt${QT_VERSION_MAJOR}CoreTools_DIR "${Qt${QT_VERSION_MAJOR}CoreTools_DIR}" 
/// @brief qt ui 工具 cmake
#define CMAKE_Qt${QT_VERSION_MAJOR}GuiTools_DIR "${Qt${QT_VERSION_MAJOR}GuiTools_DIR}" 
/// @brief qt widget 工具 cmake
#define CMAKE_Qt${QT_VERSION_MAJOR}WidgetsTools_DIR "${Qt${QT_VERSION_MAJOR}WidgetsTools_DIR}" 
/// @brief qt widget cmake
#define CMAKE_Qt${QT_VERSION_MAJOR}Widgets_DIR "${Qt${QT_VERSION_MAJOR}Widgets_DIR}" 
/// @brief qt zlb cmake
#define CMAKE_Qt${QT_VERSION_MAJOR}ZlibPrivate_DIR "${Qt${QT_VERSION_MAJOR}ZlibPrivate_DIR}"
/// @brief qt core cmake
#define CMAKE_Qt${QT_VERSION_MAJOR}Core_DIR "${Qt${QT_VERSION_MAJOR}Core_DIR}"
/// @brief qt windeployqt 执行文件路径
#define CMAKE_WINDEPLOYQT_EXECUTABLE "${WINDEPLOYQT_EXECUTABLE}"
/// @brief qt qmake 执行文件路径
#define CMAKE_QT_QMAKE_EXECUTABLE "${QT_QMAKE_EXECUTABLE}"
/// @brief 是否自动调用 ic
#define CMAKE_CMAKE_AUTOUIC "${CMAKE_AUTOUIC}" 
/// @brief 是否自动调用 moc
#define CMAKE_CMAKE_AUTOMOC "${CMAKE_AUTOMOC}"
/// @brief 是否自动调用 rcc
#define CMAKE_CMAKE_AUTORCC "${CMAKE_AUTORCC}"
#endif // CMAKE__QT_TO_C_CPP_HEADER_ENV_H_H_HEAD__FILE__
