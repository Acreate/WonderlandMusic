#ifndef TOPTOOLTITLEBARWIDGET_H_H_HEAD__FILE__
#define TOPTOOLTITLEBARWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class TopToolDockWidget;
class TopToolTitleBarWidget : public QWidget {
	Q_OBJECT;
protected:
	TopToolDockWidget *topToolDockWidget;
public:
	TopToolTitleBarWidget( TopToolDockWidget * parent );
	~TopToolTitleBarWidget( ) override;
};

#endif // TOPTOOLTITLEBARWIDGET_H_H_HEAD__FILE__
