#ifndef EVENTMACRODEFAULT_H_H_HEAD__FILE__
#define EVENTMACRODEFAULT_H_H_HEAD__FILE__

/// @brief 根据类，生成类名
/// @param class_type_ 需要的类
#define declaration_signal_class_name( class_type_ ) \
	class_type_
/// @brief 根据类，生成类声明
/// @param class_type_ 需要的类
#define declaration_signal_class_type( class_type_ ) \
	class declaration_signal_class_name( class_type_ )
/// @brief 根据类，生成类事件名称
/// @param class_type_ 需要的类
#define declaration_signal_event_info_name( class_type_ ) \
	class_type_##EventInfo
/// @brief 根据类，生成类事件类声明
/// @param class_type_ 需要的类
#define declaration_signal_event_info_type( class_type_ ) \
	class declaration_signal_event_info_name(class_type_)
/// @brief 根据类，生成类与类事件的类声明
/// @param class_type_ 需要的类
#define declaration_signal_event_info(  class_type_ ) \
	declaration_signal_class_type( class_type_ );\
	declaration_signal_event_info_type( class_type_ )

/// @brief 根据类，生成事件参数
/// @param class_type_ 需要的类
#define declaration_signal_type_args( class_type_ ) \
	declaration_signal_class_name(class_type_)* event_obj_ptr, \
	const declaration_signal_event_info_name(class_type_)& event_info_ref

/// @brief 根据类，生成调用事件参数
/// @param class_type_ 需要的类
#define declaration_signal_AppEventManage_type_args( class_type_ ) \
	AppEventManage * sender_ptr,\
	declaration_signal_class_name(class_type_)* event_obj_ptr, \
	const declaration_signal_event_info_name(class_type_)& event_info_ref
/// @brief 根据类，生成触发信号的信号名称
/// @param class_type_ 需要的类
#define declaration_AppEventManage_signal_name( class_type_ )\
	trigger_##class_type_##_signal

/// @brief 根据类，生成事件调用类的类声明
/// @param class_type_ 需要的类
#define declaration_emit_event_type( class_type_ ) \
	class declaration_emit_event_name( class_type_ )

/// @brief 根据类，生成类事件触发调用函数声明
/// @param class_type_ 需要的类
#define declaration_AppEventManage_signal( class_type_ ) \
	friend class declaration_emit_event_name( class_type_ );\
	void declaration_AppEventManage_signal_name(class_type_)(  declaration_signal_AppEventManage_type_args(class_type_) )
/// @brief 
/// @param class_type_ 需要的类
/// @param sender_ptr 信号发送者
/// @param event_obj_ptr 信号绑定类对象
/// @param event_info_ref 信号绑定类对象事件信息
#define trigger_signal( class_type_, event_obj_ptr, event_info_ref ) \
	AppEventManage *appEventManage = AppEventManage::getInstance( ); \
	emit appEventManage->declaration_AppEventManage_signal_name(class_type_)( appEventManage, event_obj_ptr, event_info_ref )

/// @brief 根据类，生成事件调用类名称
/// @param class_type_ 需要的类
#define declaration_emit_event_name( class_type_ )\
	Emit_##class_type_##_Event

/// @brief 根据类，定义事件类
/// @param class_type_ 需要的类
#define definition_emit_event( class_type_ ) \
declaration_emit_event_type(class_type_) { \
	/*只有 class_type_ 类可以生成该事件*/\
	friend declaration_signal_class_type(class_type_); \
	protected:\
	declaration_emit_event_name(class_type_)( declaration_signal_type_args( class_type_ ) ) { \
		trigger_signal( class_type_, event_obj_ptr, event_info_ref);\
	} \
}
/// @brief 根据类，定义继承事件类
/// @param class_type_ 需要的类
/// @param base_class_type_ 继承的事件类
#define definition_emit_inherit_event( class_type_ , base_class_type_) \
declaration_emit_event_type(class_type_) : public declaration_emit_event_name( base_class_type_ ){ \
	/*只有 class_type_ 类可以生成该事件*/\
	friend declaration_signal_class_type(class_type_); \
	protected:\
	declaration_emit_event_name(class_type_)( declaration_signal_type_args( base_class_type_ ) ) : declaration_emit_event_name( base_class_type_ )( event_obj_ptr, event_info_ref ) { \
	} \
}

/// @brief 根据一个类，生成一个链接信号的类的名称
/// @param class_type_ 需要的类
#define declaration_AppEventManage_connect_Type_name( class_type_ ) \
	Connect_##class_type_##_Signal
/// @brief 根据一个类，定义一个信号链接的类
/// @param class_type_ 需要的类
#define definition_AppEventManage_connect_Type( class_type_ ) \
friend class declaration_AppEventManage_connect_Type_name(class_type_); \
class declaration_AppEventManage_connect_Type_name(class_type_){ \
	public:\
	declaration_AppEventManage_connect_Type_name(class_type_)( const std::function<void (declaration_signal_AppEventManage_type_args(class_type_))> & call_function , Qt::ConnectionType connect_type = Qt::AutoConnection){\
		AppEventManage *appEventManage = AppEventManage::getInstance( ); \
		appEventManage->connect( appEventManage, &AppEventManage::declaration_AppEventManage_signal_name(class_type_), appEventManage, call_function, connect_type) ; \
	} \
}

/// @brief 根据类，生成事件消息类 __VA_ARGS__ ( 可变参数列表 ) 为枚举内容
/// @param class_type_ 需要的类
#define definition_event_info_class_type( class_type_, ... ) \
declaration_signal_event_info_type( class_type_ ) { \
	friend class class_type_; \
public:\
	/*事件类型*/ \
	enum class EventType {\
		__VA_ARGS__, \
	};\
protected:\
	/* 事件类型 */ \
	EventType event; \
	/* 事件指针对象 */ \
	class_type_ *eventSenderPtr; \
	declaration_signal_event_info_name(class_type_)( EventType event, class_type_ *event_sender_ptr )\
		: event( event ),\
		eventSenderPtr( event_sender_ptr ) {\
	}\
	declaration_signal_event_info_name(class_type_)(  ){\
	}\
public: \
	/* 获取事件类型 */ \
	virtual EventType getEventType() const { return event; } \
	/* 获取事件指针对象 */ \
	virtual class_type_* getEventSenderPtr() const { return eventSenderPtr; } \
}

/// @brief 根据类，生成继承事件消息类
/// @param class_type_ 需要的类
/// @param base_class_type_ 继承的事件消息类
#define definition_event_info_inherit_class_type( class_type_, base_class_type_ ) \
declaration_signal_event_info_type( class_type_ ) : public declaration_signal_event_info_name(base_class_type_) { \
	friend class class_type_; \
protected:\
	declaration_signal_event_info_name(class_type_)( EventType event, class_type_ *event_sender_ptr )\
		: declaration_signal_event_info_name(base_class_type_)( event, event_sender_ptr ) {\
	}\
	declaration_signal_event_info_name(class_type_)(  ): declaration_signal_event_info_name(base_class_type_)(){\
	}\
}

#endif // EVENTMACRODEFAULT_H_H_HEAD__FILE__
