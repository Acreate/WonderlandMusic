#ifndef WIDGETEFFECT_H_H_HEAD__FILE__
#define WIDGETEFFECT_H_H_HEAD__FILE__
#include <QObject>
#include <QRect>

class WidgetEffect : public QObject {
	Q_OBJECT;
protected:
	QWidget *bindWidget;
	QRect widgetRect;
	QRect widgetGeometry;
public:
	WidgetEffect( QWidget *bind_widget );
	bool eventFilter( QObject *watched, QEvent *event ) override;
	virtual bool renderEffect( ) = 0;
	~WidgetEffect( ) override;
};

#endif // WIDGETEFFECT_H_H_HEAD__FILE__
