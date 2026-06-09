#ifndef WIDGETTOOLS_H_H_HEAD__FILE__
#define WIDGETTOOLS_H_H_HEAD__FILE__

class QPoint;
class QWidget;
class WidgetTools {
public:
	/// @brief 以指定点为中心，移动源窗口，窗口的中心点为指定点
	/// @param target_pos 目标指定点
	/// @param move_source_widget 被移动的源窗口
	static void moveWidgetToCenterPos( const QPoint &target_pos, QWidget *move_source_widget );
	/// @brief 以指定窗口的中心点为中心，移动源窗口，窗口的中心点为指定点
	/// @param target_widget_pos 提供目标窗口指定点
	/// @param move_source_widget 被移动的源窗口
	static void moveWidgetToCenterPos( const QWidget *target_widget_pos, QWidget *move_source_widget );
};

#endif // WIDGETTOOLS_H_H_HEAD__FILE__
