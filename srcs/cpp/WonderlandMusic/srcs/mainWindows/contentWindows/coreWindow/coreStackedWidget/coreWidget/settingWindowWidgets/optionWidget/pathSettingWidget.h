#ifndef PATHSETTINGWIDGET_H_H_HEAD__FILE__
#define PATHSETTINGWIDGET_H_H_HEAD__FILE__

#include <QWidget>
#include <macro/eventMacroDefine.h>
class QLineEdit;
class QPushButton;
class OptionStackWidget;
class PathSettingWidget : public QWidget {
	Q_OBJECT;
protected:
	OptionStackWidget *optionStackWidget;
	/// @brief 路径提示
	QLabel *loadFileInfoPathText;
	QLineEdit *loadFileInfoPathEditInputLine;
	QPushButton *loadFileInfoPathSelectBtn;
public:
	PathSettingWidget( OptionStackWidget *parent );
	
	virtual QString getLoadFileInfoPath( ) const;
protected:
	void resizeEvent( QResizeEvent *event ) override;
};
class Event_Default_Event_Info_Type_Name( PathSettingWidget ) {
public:
	enum class EventType {
		None,
		Update_Music_info_File_Path_Info
	};
protected:
	EventType eventType;
public:
	virtual ~PathSettingWidgetEventInfo( ) = default;
	PathSettingWidgetEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // PATHSETTINGWIDGET_H_H_HEAD__FILE__
