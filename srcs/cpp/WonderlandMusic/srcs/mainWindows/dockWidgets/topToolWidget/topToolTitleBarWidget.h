#ifndef TOPTOOLTITLEBARWIDGET_H_H_HEAD__FILE__
#define TOPTOOLTITLEBARWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../../../baseWidget/baseWidget.h"
class TopToolDockWidget;
class TopToolTitleBarWidget : public BaseWidget {
	Q_OBJECT;
protected:
	TopToolDockWidget *topToolDockWidget;
public:
	TopToolTitleBarWidget( TopToolDockWidget * parent );
	~TopToolTitleBarWidget( ) override;
};

#endif // TOPTOOLTITLEBARWIDGET_H_H_HEAD__FILE__
