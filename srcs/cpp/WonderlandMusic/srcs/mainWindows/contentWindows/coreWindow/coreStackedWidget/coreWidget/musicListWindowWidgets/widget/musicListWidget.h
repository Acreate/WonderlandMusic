#ifndef MUSICLISTWIDGET_H_H_HEAD__FILE__
#define MUSICLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class MusicListWidget : public QWidget {
	Q_OBJECT;
public:
	MusicListWidget( QWidget *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICLISTWIDGET_H_H_HEAD__FILE__
