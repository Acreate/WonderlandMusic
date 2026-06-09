#ifndef EVENTMACRODEFINE_H_H_HEAD__FILE__
#define EVENTMACRODEFINE_H_H_HEAD__FILE__

/// @brief 生成友元事件类名
/// @param event_name 事件类名
#define Event_Default_Event_Class_Type_Name( event_name ) \
		event_name##Event

/// @brief 生成事件触发函数类名
/// @param event_name 事件函数类名
#define Event_Default_Event_Call_Function_Name( event_name ) \
		 trigger##event_name##Event
/// @brief 生成事件触发函数类名
/// @param event_name 事件函数类名
#define Event_Default_Event_Info_Type_Name( event_name ) \
		event_name##EventInfo

/// @brief 声明一个类型
/// @param event_name 声明的类
#define Event_Declare_Event_Info_Type_Name( event_name ) \
	class event_name; \
	class Event_Default_Event_Info_Type_Name( event_name )

/// @brief 生成事件触发函数类名
/// @param event_name 事件函数类名，并且作为 消息类型名称（使用 Event_Default_Event_Info_Type_Name 宏）
/// @param receive_class_type 接受信号的类型
#define Event_Default_Event_Call_Function( event_name, receive_class_type ) \
		void Event_Default_Event_Call_Function_Name(event_name)( receive_class_type *receive, event_name *sender, const Event_Default_Event_Info_Type_Name(event_name) &info )

/// @brief 生成事件触发函数类名
/// @param event_name 事件函数类名，并且作为 消息类型名称（使用 Event_Default_Event_Info_Type_Name 宏）
#define Event_Default_Receive_Call_Function( event_name ) \
		void Event_Default_Event_Call_Function_Name(event_name)( event_name *sender, const Event_Default_Event_Info_Type_Name(event_name) &info )

/// @brief 生成事件调用静态函数类
/// @param event_name 事件名称，并且作为该类的名称，并作为消息发送方，生成该类友元，可访问该静态成员的函数，并且作为 消息类型名称（使用 Event_Default_Event_Info_Type_Name 宏）
/// @param receive_class_type 接受信号的类型，并且使用该变量进行调用，需在类中配置友元(可使用 Event_Friend_Macro 宏配置)
#define Event_Define_Event_Class_type( event_name, receive_class_type)  \
class Event_Default_Event_Class_Type_Name(event_name) { \
	friend class event_name;  \
	Event_Default_Event_Class_Type_Name(event_name)(receive_class_type *receive, event_name *sender, const Event_Default_Event_Info_Type_Name(event_name) &info ){ \
	Event_Default_Event_Class_Type_Name(event_name)::Event_Default_Event_Call_Function_Name(event_name)(receive, sender, info ); \
	}\
	static Event_Default_Event_Call_Function(event_name,receive_class_type){ \
		receive->Event_Default_Event_Call_Function_Name(event_name)( sender, info ); \
	}\
}

#endif // EVENTMACRODEFINE_H_H_HEAD__FILE__
