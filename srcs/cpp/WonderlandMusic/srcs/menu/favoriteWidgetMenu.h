#ifndef FAVORITEWIDGETMENU_H_H_HEAD__FILE__
#define FAVORITEWIDGETMENU_H_H_HEAD__FILE__
#include <QMenu>

#include "../interface/iAppCore.h"

class FavoriteItemWidget;

class FavoriteWidgetMenu : public QMenu, public IAppCore {
	Q_OBJECT;

protected:
	FavoriteItemWidget *labelWidget = nullptr;
	/// @brief 添加收藏夹
	QAction *addFavorite = nullptr;
	/// @brief 删除收藏夹
	QAction *deleteFavorite = nullptr;
	/// @brief 更改收藏夹
	QAction *changeFavorite = nullptr;

public:
	FavoriteWidgetMenu( );

	~FavoriteWidgetMenu( ) override;

protected:
	bool deleteResource( ) override;

public:
	virtual FavoriteItemWidget * getLabelWidget( ) const;

	bool initBefore( ) override;

	bool init( ) override;

	bool initAfter( ) override;
Q_SIGNALS:
	void signal_add( );
	void signal_del( );
	void signal_change( );
};

#endif // FAVORITEWIDGETMENU_H_H_HEAD__FILE__
