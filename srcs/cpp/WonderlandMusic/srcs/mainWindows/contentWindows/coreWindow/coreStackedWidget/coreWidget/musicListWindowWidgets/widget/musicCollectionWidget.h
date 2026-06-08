#ifndef MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
#define MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include <base/baseWidget/baseWidget.h>

class CollectionItemWidget;
class CollectionTopToolWidget;
class MusicCollectionWidget : public BaseWidget {
	Q_OBJECT;
protected:
	CollectionTopToolWidget *collectionTopToolWidget;
	CollectionItemWidget *collectionItemWidget;
public:
	MusicCollectionWidget( QWidget *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
