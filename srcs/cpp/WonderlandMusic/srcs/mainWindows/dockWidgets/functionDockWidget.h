#ifndef FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__
#define FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__


#include <base/baseWidget/baseDockWidget.h>


class FunctionWidget;
class MainWindow;

// 事件头文件
#include <macro/eventMacroDefine.h>

/// @brief 功能面板
class FunctionDockWidget : public BaseDockWidget {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	FunctionWidget *functionWidget;
public:
	FunctionDockWidget( MainWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#define FunctionDockWidgetEventTypeName Event_Default_Event_Info_Type_Name( FunctionDockWidget )
class FunctionDockWidgetEventTypeName {
public:
	enum class EventType {
		None,
		Show_Music,
		Show_Setting,
	};
protected:
	EventType type;
public:
	virtual ~FunctionDockWidgetEventTypeName( ) = default;
	FunctionDockWidgetEventTypeName( const EventType type )
		: type( type ) { }
	virtual EventType getType( ) const { return type; }
};

#endif // FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__
