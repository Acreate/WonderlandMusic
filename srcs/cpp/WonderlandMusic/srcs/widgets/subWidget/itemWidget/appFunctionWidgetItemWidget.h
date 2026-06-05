#ifndef APPFUNCTIONWIDGETITEMWIDGET_H_H_HEAD__FILE__
#define APPFUNCTIONWIDGETITEMWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class AppFunctionWidget;
class AppFunctionWidgetItemWidget : public QWidget {
	Q_OBJECT;
protected:
	QString itemName;
	QImage renderItem;
	AppFunctionWidget *parent;
public:
	AppFunctionWidgetItemWidget( AppFunctionWidget *parent, const QString &item_name );
	~AppFunctionWidgetItemWidget( ) override;
	virtual const QString & getItemName( ) const { return itemName; }
	virtual void setItemName( const QString &item_name );
protected:
	void paintEvent( QPaintEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};

#endif // APPFUNCTIONWIDGETITEMWIDGET_H_H_HEAD__FILE__
