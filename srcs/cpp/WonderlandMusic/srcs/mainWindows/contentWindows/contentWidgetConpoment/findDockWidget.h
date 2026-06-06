#ifndef FINDDOCKWIDGET_H_H_HEAD__FILE__
#define FINDDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
#include <macro/eventMacroDefine.h>
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

#define FindDockWidgetEventTypeName Event_Default_Event_Info_Type_Name( FindDockWidget )
class FindDockWidgetEventTypeName {

};
#endif // FINDDOCKWIDGET_H_H_HEAD__FILE__
