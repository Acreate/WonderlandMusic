#ifndef PLAYERCONTROLWIDGETSCROLLAREA_H_H_HEAD__FILE__
#define PLAYERCONTROLWIDGETSCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

class PlayWindow;

class PlayerControlWidgetScrollArea : public QScrollArea {
	Q_OBJECT;

public:
	PlayerControlWidgetScrollArea( PlayWindow *play_window );
	~PlayerControlWidgetScrollArea( ) override;

protected:
	void mouseDoubleClickEvent( QMouseEvent * ) override;
	void mouseMoveEvent( QMouseEvent * ) override;
	void mousePressEvent( QMouseEvent * ) override;
	void mouseReleaseEvent( QMouseEvent * ) override;
};

#endif // PLAYERCONTROLWIDGETSCROLLAREA_H_H_HEAD__FILE__
