#ifndef FAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define FAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../interface/iAppJsonData.h"
class FavoriteItem;
class MusicItem;
class QLineEdit;

class FavoriteItemWidget : public QWidget, public IAppJsonData {
	Q_OBJECT;
	friend class FavoriteItem;

protected:
	QLineEdit *lineEdit;
	FavoriteItem *favoriteItem;
	FavoriteItemWidget( FavoriteItem *favor_item );

public:
	~FavoriteItemWidget( ) override;
	virtual QString getFavoriteName( ) const;
	virtual void setFavoriteName( const QString &name );
	virtual void updateWidth( );
	virtual FavoriteItem * getFavorItem( ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void focusOutEvent( QFocusEvent *event ) override;
	void enterEvent( QEnterEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
Q_SIGNALS:
	void signal_change_name_finished( FavoriteItemWidget *item );
	void signal_click_item( FavoriteItemWidget *item );
	void signal_enter_item( FavoriteItemWidget *item );
	void signal_leave_item( FavoriteItemWidget *item );
};
#endif // FAVORITEITEMWIDGET_H_H_HEAD__FILE__
