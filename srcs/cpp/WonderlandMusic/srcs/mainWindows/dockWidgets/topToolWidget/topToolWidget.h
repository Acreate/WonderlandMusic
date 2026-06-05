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
public:
	TopToolWidget( TopToolDockWidget *parent );
protected:
	void resizeEvent( QResizeEvent *event ) override;
};
class TopToolEventInfo {
public:
	enum class Type {
		Close,
		Min
	};
protected:
	Type type;
public:
	virtual ~TopToolEventInfo( ) = default;
	TopToolEventInfo( const Type type )
		: type( type ) { }
	virtual Type getType( ) const { return type; }
};
#endif // TOPTOOLWIDGET_H_H_HEAD__FILE__
