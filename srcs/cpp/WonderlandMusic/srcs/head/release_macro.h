#ifndef RELEASE_MACRO_H_H_HEAD__FILE__
#define RELEASE_MACRO_H_H_HEAD__FILE__

#include <tools/classTypeTools.h>
#include <msgInfo/messageErrorOut.h>
#include <msgInfo/messageString.h>
#include "call_class_native_function.h"

/// @brief 删除一个指针对象，并且该对象赋值为 nullptr
/// @param ptr 删除的指针对象
#define Delete_Resource_App_Core_Ptr( ptr ) if( ptr ) ( delete ptr, ptr = nullptr )

#endif // RELEASE_MACRO_H_H_HEAD__FILE__
