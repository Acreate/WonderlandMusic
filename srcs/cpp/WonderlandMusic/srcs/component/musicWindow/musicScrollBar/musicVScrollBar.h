#ifndef MUSICVSCROLLBAR_H_H_HEAD__FILE__
#define MUSICVSCROLLBAR_H_H_HEAD__FILE__
#include <QScrollBar>

class MusicVScrollBar : public QScrollBar {
	Q_OBJECT;

public:
	MusicVScrollBar( QWidget *parent = nullptr );

protected:
	void mouseMoveEvent( QMouseEvent * ) override;
	void mousePressEvent( QMouseEvent * ) override;
	void mouseReleaseEvent( QMouseEvent * ) override;
};

#endif // MUSICVSCROLLBAR_H_H_HEAD__FILE__
