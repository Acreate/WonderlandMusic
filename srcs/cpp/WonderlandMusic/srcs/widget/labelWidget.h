#ifndef LABELWIDGET_H_H_HEAD__FILE__
#define LABELWIDGET_H_H_HEAD__FILE__
#include <QLabel>

class LabelWidget : public QLabel {
	Q_OBJECT;

protected:
	bool click;

public:
	LabelWidget( const QString &text, QWidget *parent, const Qt::WindowFlags &f );

	LabelWidget( const QString &text, QWidget *parent );

	LabelWidget( const QString &text );

	LabelWidget( );

protected:
	void mousePressEvent( QMouseEvent *ev ) override;

	void mouseReleaseEvent( QMouseEvent *ev ) override;
};

#endif // LABELWIDGET_H_H_HEAD__FILE__
