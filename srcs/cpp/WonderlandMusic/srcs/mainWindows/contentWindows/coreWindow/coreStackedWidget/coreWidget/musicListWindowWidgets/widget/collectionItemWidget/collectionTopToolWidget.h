#ifndef COLLECTIONTOPTOOLWIDGET_H_H_HEAD__FILE__
#define COLLECTIONTOPTOOLWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class CollectionTopToolWidget : public BaseWidget {
	Q_OBJECT;
protected:
	QLabel *title;
public:
	CollectionTopToolWidget( QWidget *parent );
	~CollectionTopToolWidget( ) override;
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // COLLECTIONTOPTOOLWIDGET_H_H_HEAD__FILE__
