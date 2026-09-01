#ifndef MUSICHSCROLLBAR_H_H_HEAD__FILE__
#define MUSICHSCROLLBAR_H_H_HEAD__FILE__
#include <QScrollBar>

class MusicHScrollBar : public QScrollBar {
	Q_OBJECT;

public:
	MusicHScrollBar( QWidget *parent = nullptr );
	~MusicHScrollBar( ) override;

protected:
	void mouseMoveEvent( QMouseEvent * ) override;
	void mousePressEvent( QMouseEvent * ) override;
	void mouseReleaseEvent( QMouseEvent * ) override;
};

#endif // MUSICHSCROLLBAR_H_H_HEAD__FILE__
