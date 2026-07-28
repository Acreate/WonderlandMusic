#ifndef TITLEVERTICALSCROLLBAR_H_H_HEAD__FILE__
#define TITLEVERTICALSCROLLBAR_H_H_HEAD__FILE__
#include <QScrollBar>

class TitleVerticalScrollBar : public QScrollBar {
	Q_OBJECT;

public:
	TitleVerticalScrollBar( QWidget *parent );

protected:
	void changeEvent( QEvent *e ) override;
	void keyPressEvent( QKeyEvent *ev ) override;
	void sliderChange( SliderChange change ) override;
	void wheelEvent( QWheelEvent * ) override;
};

#endif // TITLEVERTICALSCROLLBAR_H_H_HEAD__FILE__
