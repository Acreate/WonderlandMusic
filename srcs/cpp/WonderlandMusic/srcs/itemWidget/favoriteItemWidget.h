#ifndef FAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define FAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class PlayerListWidget;
class PlayerWindow;
class FavoriteWidget;

class FavoriteItemWidget : public QWidget {
	Q_OBJECT;

protected:
	friend class FavoriteWidget;
	friend class PlayerWindow;
	QString name;
	PlayerListWidget *bindPlayerListWidget;
	FavoriteWidget *parent;

	FavoriteItemWidget( FavoriteWidget *parent, const QString &name );

	FavoriteItemWidget( FavoriteWidget *parent, PlayerListWidget *bind_player_list_widget, const QString &name );

public:
};

#endif // FAVORITEITEMWIDGET_H_H_HEAD__FILE__
