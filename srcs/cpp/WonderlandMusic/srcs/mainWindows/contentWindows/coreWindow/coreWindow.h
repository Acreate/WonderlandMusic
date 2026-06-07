#ifndef COREWINDOW_H_H_HEAD__FILE__
#define COREWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
#include <macro/eventMacroDefine.h>
class CoreStackedWidget;
class CoreStackedWidgeEventInfo;
class ContentWindow;


class CoreWindow : public QMainWindow {
	Q_OBJECT;
protected:
	/// @brief 父窗口
	ContentWindow *contentWindow;
	/// @brief 堆叠的窗口
	CoreStackedWidget *coreStackedWidget;
public:
	CoreWindow( ContentWindow *parent );
};

#define CoreWindowEventTypeName Event_Default_Event_Info_Type_Name( CoreWindow )
class CoreWindowEventTypeName {

};

#endif // COREWINDOW_H_H_HEAD__FILE__
