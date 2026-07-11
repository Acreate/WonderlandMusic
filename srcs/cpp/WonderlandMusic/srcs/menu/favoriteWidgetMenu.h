#ifndef FAVORITEWIDGETMENU_H_H_HEAD__FILE__
#define FAVORITEWIDGETMENU_H_H_HEAD__FILE__
#include <QMenu>
#include "../interface/iAppCore.h"
class FavoriteItem;

class FavoriteWidgetMenu : public QMenu, public IAppCore {
	Q_OBJECT;
	friend class AppMenuManage;

protected:
	FavoriteItem *labelWidget = nullptr;
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
	virtual void setLabelWidget( FavoriteItem *const label_widget );

public:
	virtual FavoriteItem * getLabelWidget( ) const;
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
Q_SIGNALS:
	void signal_add( );
	void signal_del( );
	void signal_change( );
};
#endif // FAVORITEWIDGETMENU_H_H_HEAD__FILE__
