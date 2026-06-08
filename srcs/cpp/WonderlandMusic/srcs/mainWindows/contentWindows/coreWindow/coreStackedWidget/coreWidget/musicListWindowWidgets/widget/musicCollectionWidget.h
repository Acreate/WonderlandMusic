#ifndef MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
#define MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../../../../../../../baseWidget/baseWidget.h"
class MusicCollectionWidget : public BaseWidget {
	Q_OBJECT;
public:
	MusicCollectionWidget( QWidget *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
