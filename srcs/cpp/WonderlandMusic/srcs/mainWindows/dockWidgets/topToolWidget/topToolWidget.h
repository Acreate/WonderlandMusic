#ifndef TOPTOOLWIDGET_H_H_HEAD__FILE__
#define TOPTOOLWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../../../baseWidget/baseWidget.h"
class QPushButton;
class TopToolDockWidget;

// 事件头文件
#include <macro/eventMacroDefine.h>


class TopToolWidget : public BaseWidget {
	Q_OBJECT;
protected:
	TopToolDockWidget *topToolDockWidget;
	QPushButton *closeBtn;
	QPushButton *minMainWindowBtn;
	bool drawWindow;
	QPoint oldMousePos;
	QPoint newMousePos;
public:
	TopToolWidget( TopToolDockWidget *parent );
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
};
#define TopToolWidgetEventTypeName Event_Default_Event_Info_Type_Name( TopToolWidget )
class TopToolWidgetEventTypeName {
	friend class TopToolWidget;
public:
	enum class Type {
		Close,
		Min,
		MoveTargetOffsetWindow
	};
protected:
	Type type;
	QPoint oldMousePos;
	QPoint newMousePos;
public:
	virtual ~TopToolWidgetEventTypeName( ) = default;
	TopToolWidgetEventTypeName( const Type type ) : type( type ) { }
	TopToolWidgetEventTypeName( const QPoint &old_mouse_pos, const QPoint &new_mouse_pos )
		: type( Type::MoveTargetOffsetWindow ),
		oldMousePos( old_mouse_pos ),
		newMousePos( new_mouse_pos ) { }
	virtual const QPoint * getOldMousePos( ) const { return &oldMousePos; }
	virtual const QPoint * getNewMousePos( ) const { return &newMousePos; }
	virtual Type getType( ) const { return type; }
};
#endif // TOPTOOLWIDGET_H_H_HEAD__FILE__
