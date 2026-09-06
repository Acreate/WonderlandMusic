#ifndef PLAYERINFOLISTWIDGETSCROLLAREA_H_H_HEAD__FILE__
#define PLAYERINFOLISTWIDGETSCROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

class PlayWindow;

class PlayerInfoListWidgetScrollArea : public QScrollArea {
	Q_OBJECT;

public:
	PlayerInfoListWidgetScrollArea( PlayWindow *play_window );
	~PlayerInfoListWidgetScrollArea( ) override;

protected:
	void mouseDoubleClickEvent( QMouseEvent * ) override;
	void mouseMoveEvent( QMouseEvent * ) override;
	void mousePressEvent( QMouseEvent * ) override;
	void mouseReleaseEvent( QMouseEvent * ) override;
};

#endif // PLAYERINFOLISTWIDGETSCROLLAREA_H_H_HEAD__FILE__
