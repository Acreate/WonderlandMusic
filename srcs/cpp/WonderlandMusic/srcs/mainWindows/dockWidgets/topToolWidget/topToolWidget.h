#ifndef TOPTOOLWIDGET_H_H_HEAD__FILE__
#define TOPTOOLWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class QPushButton;
class TopToolDockWidget;
class TopToolWidget : public QWidget {
	Q_OBJECT;
protected:
	TopToolDockWidget *parent;
	QPushButton* closeBtn;
	QPushButton* minMainWindowBtn;
public:
	TopToolWidget( TopToolDockWidget *parent );
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // TOPTOOLWIDGET_H_H_HEAD__FILE__
