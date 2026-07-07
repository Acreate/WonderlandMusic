#ifndef FAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define FAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class MusicItem;
class QLineEdit;

class FavoriteItemWidget : public QWidget {
	Q_OBJECT;
	friend class AppMusicManage;

protected:
	QLineEdit *lineEdit;

public:
	~FavoriteItemWidget( ) override;
	FavoriteItemWidget( );
	FavoriteItemWidget( QWidget *parent );
	virtual QString getFavoriteName( ) const;
	virtual void setFavoriteName( const QString &name );
	virtual void updateWidth( );

protected:
	void mouseDoubleClickEvent( QMouseEvent *event ) override;
	void focusOutEvent( QFocusEvent *event ) override;
Q_SIGNALS:
	void signal_change_name_finished( );
};

#endif // FAVORITEITEMWIDGET_H_H_HEAD__FILE__
