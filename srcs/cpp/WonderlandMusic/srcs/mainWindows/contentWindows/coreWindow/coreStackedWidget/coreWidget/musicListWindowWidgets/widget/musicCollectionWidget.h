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
	std::vector< CollectionItemWidget * > collectionItemWidgets;
public:
	MusicCollectionWidget( QWidget *parent );
	~MusicCollectionWidget( ) override;
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // MUSICCOLLECTIONWIDGET_H_H_HEAD__FILE__
