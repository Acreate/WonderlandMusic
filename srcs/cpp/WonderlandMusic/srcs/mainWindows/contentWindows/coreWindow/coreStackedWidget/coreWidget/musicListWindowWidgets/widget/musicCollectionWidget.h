#ifndef MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
#define MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class MusicCollectionWidget : public QWidget {
	Q_OBJECT;
public:
	MusicCollectionWidget( QWidget *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
