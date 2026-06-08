#ifndef FINDDOCKWIDGET_H_H_HEAD__FILE__
#define FINDDOCKWIDGET_H_H_HEAD__FILE__

#include <macro/eventMacroDefine.h>

#include <base/baseWidget/baseDockWidget.h>
class ContentWindow;
class FindDockWidget : public BaseDockWidget {
	Q_OBJECT;
protected:
	ContentWindow *contentWindow;
public:
	FindDockWidget( ContentWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#define FindDockWidgetEventTypeName Event_Default_Event_Info_Type_Name( FindDockWidget )
class FindDockWidgetEventTypeName {

};
#endif // FINDDOCKWIDGET_H_H_HEAD__FILE__
