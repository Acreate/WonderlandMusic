#ifndef APPFUNCTIONWIDGET_H_H_HEAD__FILE__
#define APPFUNCTIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class AppFunctionItem;
/// @brief 软件功能面板
class AppFunctionWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 偏移
	QPoint offset;
	/// @brief 功能节点列表
	std::vector< AppFunctionItem * > appFunctionItems;
public:
	AppFunctionWidget( QWidget *parent = nullptr );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	/// @brief 功能项被点击
	/// @param click_item 点击项
	void clickFunctionItem( const AppFunctionItem &click_item );
};

#endif // APPFUNCTIONWIDGET_H_H_HEAD__FILE__
