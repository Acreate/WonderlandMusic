#ifndef TOPTOOLWIDGET_H_H_HEAD__FILE__
#define TOPTOOLWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class QPushButton;
class TopToolDockWidget;
class TopToolWidget : public QWidget {
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
class TopToolEventInfo {
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
	virtual ~TopToolEventInfo( ) = default;
	TopToolEventInfo( const Type type ) : type( type ) { }
	TopToolEventInfo( const QPoint &old_mouse_pos, const QPoint &new_mouse_pos )
		: type( Type::MoveTargetOffsetWindow ),
		oldMousePos( old_mouse_pos ),
		newMousePos( new_mouse_pos ) { }
	virtual const QPoint * getOldMousePos( ) const { return &oldMousePos; }
	virtual const QPoint * getNewMousePos( ) const { return &newMousePos; }
	virtual Type getType( ) const { return type; }
};
#endif // TOPTOOLWIDGET_H_H_HEAD__FILE__
