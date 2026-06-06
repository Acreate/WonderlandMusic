#ifndef CORESTACKEDWIDGET_H_H_HEAD__FILE__
#define CORESTACKEDWIDGET_H_H_HEAD__FILE__

#include <QStackedWidget>

#include <macro/eventMacroDefine.h>

#define SettingWindowEventClassName Event_Default_ClassName( SettingWindow )
#define SettingWindowDefaultEventCallFunction Event_Default_Receive_Call_Function( SettingWindow )
#define SettingWindowEventDefineClass Event_Define_Event_Class_type( SettingWindow, CoreStackedWidget )
class Event_Default_Event_Info_Type_Name( SettingWindow );

class SettingWindow;
class MusicListWindow;
class CoreWindow;
class CoreStackedWidget : public QStackedWidget {
	friend class SettingWindowEventClassName;
	Q_OBJECT;
protected:
	CoreWindow *coreWindow;
	MusicListWindow *musicListWindow;
	SettingWindow *settingWindow;
public:
	CoreStackedWidget( CoreWindow *parent );
	/// @brief 显示音乐面板
	/// @return 失败返回 false
	virtual bool showMusicWidget( );
	/// @brief 显示设置面板
	/// @return 失败返回 false
	virtual bool showSettingWidget( );
private:
	virtual SettingWindowDefaultEventCallFunction;
};

#define CoreStackedWidgetEventTypeName Event_Default_Event_Info_Type_Name( CoreStackedWidget )
class CoreStackedWidgetEventTypeName {

};
SettingWindowEventDefineClass;
#endif // CORESTACKEDWIDGET_H_H_HEAD__FILE__
