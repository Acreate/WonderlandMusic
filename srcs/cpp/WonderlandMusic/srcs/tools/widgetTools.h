#ifndef WIDGETTOOLS_H_H_HEAD__FILE__
#define WIDGETTOOLS_H_H_HEAD__FILE__

class QMenu;
class QPoint;
class QWidget;

namespace WidgetTools {
	/// @brief 以指定点为中心，移动源窗口，窗口的中心点为指定点
	/// @param target_pos 目标指定点
	/// @param move_source_widget 被移动的源窗口
	void moveWidgetToCenterPos( const QPoint &target_pos, QWidget *move_source_widget );

	/// @brief 以指定窗口的中心点为中心，移动源窗口，窗口的中心点为指定点
	/// @param target_widget_pos 提供目标窗口指定点
	/// @param move_source_widget 被移动的源窗口
	void moveWidgetToCenterPos( const QWidget *target_widget_pos, QWidget *move_source_widget );

	/// @brief 获取显示菜单的建议位置
	/// @param suggestion_show_pos 返回的建议位置
	/// @param org_pos 原始显示的位置
	/// @param calculation_menu 显示菜单
	/// @return 失败返回 false
	bool getMenuSuggestionShowMenuPos( QPoint &suggestion_show_pos, const QPoint &org_pos, QMenu *calculation_menu );
}

#endif // WIDGETTOOLS_H_H_HEAD__FILE__
