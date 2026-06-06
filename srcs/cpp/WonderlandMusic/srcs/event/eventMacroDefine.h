#ifndef EVENTMACRODEFINE_H_H_HEAD__FILE__
#define EVENTMACRODEFINE_H_H_HEAD__FILE__

/// @brief 生成友元事件类名
/// @param event_name 事件类名
#define Event_Default_ClassName( event_name ) \
		event_name##Event

/// @brief 生成事件触发函数类名
/// @param event_name 事件函数类名
#define Event_Default_Event_Call_Function_Name( event_name ) \
		 trigger##event_name##Event

/// @brief 生成事件调用静态函数类
/// @param event_name 事件名称，并且作为该类的名称
/// @param receive_class_type 接受信号的类型，并且使用该变量进行调用，需在类中配置友元(可使用 Event_Friend_Macro 宏配置)
/// @param friend_class_type 消息发送方，生成该类友元，可访问该静态成员的函数
/// @param event_info 消息类型
#define Event_Define_Event_Class_type( event_name, receive_class_type, friend_class_type, event_info)  \
class Event_Default_ClassName(event_name) { \
	friend class friend_class_type;  \
	static size_t Event_Default_Event_Call_Function_Name(event_name)( receive_class_type *receive, friend_class_type *sender, const event_info &info ) { \
		return receive->Event_Default_Event_Call_Function_Name(event_name)( sender, info ); \
	}\
}

#endif // EVENTMACRODEFINE_H_H_HEAD__FILE__
