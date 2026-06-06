#ifndef PATHSETTINGWIDGET_H_H_HEAD__FILE__
#define PATHSETTINGWIDGET_H_H_HEAD__FILE__

#include <QWidget>
#include <macro/eventMacroDefine.h>
class OptionStackWidget;
class PathSettingWidget : public QWidget {
	Q_OBJECT;
protected:
	OptionStackWidget *optionStackWidget;
public:
	PathSettingWidget( OptionStackWidget *parent );

};
class Event_Default_Event_Info_Type_Name( PathSettingWidget ) {

};
#endif // PATHSETTINGWIDGET_H_H_HEAD__FILE__
