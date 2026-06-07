#ifndef OPTIONSTACKWIDGET_H_H_HEAD__FILE__
#define OPTIONSTACKWIDGET_H_H_HEAD__FILE__

#include <QStackedWidget>
#include <macro/eventMacroDefine.h>
class PathSettingWidget;
class AboutApplicationWidget;
class SettingWindow;
/// @brief 堆叠配置窗口
class OptionStackWidget : public QStackedWidget {
	Q_OBJECT;
protected:
	SettingWindow *settingWindow;
	PathSettingWidget *pathSettingWidget;
	AboutApplicationWidget *aboutApplicationWidget;
public:
	OptionStackWidget( SettingWindow *parent );
};

class Event_Default_Event_Info_Type_Name( OptionStackWidget ) {
public:
	enum class EnventType {
		None,
		Save,
		Cencel
	};
protected:
	EnventType enventType;
public:
	virtual ~OptionStackWidgetEventInfo( ) = default;
	OptionStackWidgetEventInfo( const EnventType envent_type )
		: enventType( envent_type ) { }
	virtual EnventType getEnventType( ) const { return enventType; }
};

#endif // OPTIONSTACKWIDGET_H_H_HEAD__FILE__
