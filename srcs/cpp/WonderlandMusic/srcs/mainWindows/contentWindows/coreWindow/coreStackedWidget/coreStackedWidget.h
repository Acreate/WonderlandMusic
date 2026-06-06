#ifndef CORESTACKEDWIDGET_H_H_HEAD__FILE__
#define CORESTACKEDWIDGET_H_H_HEAD__FILE__

#include <QStackedWidget>
class SettingWindow;
class MusicListWindow;
class CoreWindow;
class CoreStackedWidget : public QStackedWidget {
	Q_OBJECT;
protected:
	CoreWindow *coreWindow;
	MusicListWindow *musicListWindow;
	SettingWindow *settingWindow;
public:
	CoreStackedWidget( CoreWindow *parent );
};

#include <event/eventMacroDefine.h>
#define CoreStackedWidgetEventTypeName Event_Default_Event_Info_Type_Name( CoreStackedWidget )
class CoreStackedWidgetEventTypeName {

};

#endif // CORESTACKEDWIDGET_H_H_HEAD__FILE__
