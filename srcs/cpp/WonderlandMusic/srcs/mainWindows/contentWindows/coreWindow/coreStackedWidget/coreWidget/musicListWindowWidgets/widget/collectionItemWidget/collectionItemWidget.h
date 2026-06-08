#ifndef COLLECTIONITEMWIDGET_H_H_HEAD__FILE__
#define COLLECTIONITEMWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class CollectionItemWidget : public BaseWidget {
	Q_OBJECT;
protected:
	QLabel *itemTitleLable;
public:
	CollectionItemWidget( QWidget *parent );
	virtual QString getTitleName( ) const;
	virtual void setTitleName( const QString &new_title_name ) const;
protected:
	void resizeEvent( QResizeEvent *event ) override;
};

#endif // COLLECTIONITEMWIDGET_H_H_HEAD__FILE__
