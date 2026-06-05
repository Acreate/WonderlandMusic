#ifndef APPFUNCTIONWIDGET_H_H_HEAD__FILE__
#define APPFUNCTIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>
/// @brief 软件功能面板
class AppFunctionWidget : public QWidget {
	Q_OBJECT;
public:
	AppFunctionWidget( QWidget *parent = nullptr ) : QWidget( parent ) { }
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // APPFUNCTIONWIDGET_H_H_HEAD__FILE__
