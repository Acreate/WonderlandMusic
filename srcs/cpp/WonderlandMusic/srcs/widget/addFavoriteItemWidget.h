#ifndef ADDFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define ADDFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../interface/iAppCore.h"

class AddFavoriteItemWidget : public QWidget, public IAppCore {
	Q_OBJECT;

public:
	AddFavoriteItemWidget( QWidget *parent );
	~AddFavoriteItemWidget( ) override;

protected:
	bool deleteResource( ) override;
public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
Q_SIGNALS:
	void click_ok_btn( AddFavoriteItemWidget *add_favorite_item_widget );
	void click_cancel_btn( AddFavoriteItemWidget *add_favorite_item_widget );
};
#endif // ADDFAVORITEITEMWIDGET_H_H_HEAD__FILE__
