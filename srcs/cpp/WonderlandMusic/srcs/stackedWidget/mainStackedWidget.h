#ifndef MAINSTACKEDWIDGET_H_H_HEAD__FILE__
#define MAINSTACKEDWIDGET_H_H_HEAD__FILE__

#include <QStackedWidget>
class MainStackedWidget : public QStackedWidget {
	Q_OBJECT;
public:
	MainStackedWidget( QWidget *parent ) : QStackedWidget( parent ) { }
};

#endif // MAINSTACKEDWIDGET_H_H_HEAD__FILE__
