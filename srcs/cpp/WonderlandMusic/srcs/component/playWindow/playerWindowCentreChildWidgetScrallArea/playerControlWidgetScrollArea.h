#ifndef PLAYERCONTROLWIDGETSCROLLAREA_H_H_HEAD__FILE__
#define PLAYERCONTROLWIDGETSCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

#include "../../../classTypeInfo/classTypeInfoVar.h"

class IPlayerWindowCentreWidget;
class PlayWindow;

class PlayerControlWidgetScrollArea : public QScrollArea, public virtual ClassTypeInfoVar {
	Q_OBJECT;

public:
	PlayerControlWidgetScrollArea( );
	~PlayerControlWidgetScrollArea( ) override;

protected:
	void mouseDoubleClickEvent( QMouseEvent * ) override;
	void mouseMoveEvent( QMouseEvent * ) override;
	void mousePressEvent( QMouseEvent * ) override;
	void mouseReleaseEvent( QMouseEvent * ) override;
};

#endif // PLAYERCONTROLWIDGETSCROLLAREA_H_H_HEAD__FILE__
