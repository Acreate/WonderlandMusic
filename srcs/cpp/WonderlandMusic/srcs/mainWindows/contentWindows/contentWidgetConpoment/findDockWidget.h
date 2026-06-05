#ifndef FINDDOCKWIDGET_H_H_HEAD__FILE__
#define FINDDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
class ContentWindow;
class FindDockWidget : public QDockWidget {
	Q_OBJECT;
protected:
	ContentWindow *contentWindow;
public:
	FindDockWidget( ContentWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

class FindInfo {

};
#endif // FINDDOCKWIDGET_H_H_HEAD__FILE__
