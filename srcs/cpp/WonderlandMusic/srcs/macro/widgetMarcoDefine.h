#ifndef WIDGETMARCODEFINE_H_H_HEAD__FILE__
#define WIDGETMARCODEFINE_H_H_HEAD__FILE__

/// @brief 使堆栈窗口显示指定的窗口，失败返回 false
/// @param stack_widget 堆栈窗口指针
/// @param show_widget 显示的窗口
#define Stack_Widget_Show_Widget( stack_widget, show_widget ) \
	if(stack_widget-> currentWidget( ) == show_widget ) \
		return true; \
	stack_widget->setCurrentWidget( show_widget ); \
	if( stack_widget->currentWidget( ) == show_widget ) \
		return true;\
	return false

#endif // WIDGETMARCODEFINE_H_H_HEAD__FILE__
