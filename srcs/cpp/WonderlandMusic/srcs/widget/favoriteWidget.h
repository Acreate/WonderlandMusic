#ifndef FAVORITEWIDGET_H_H_HEAD__FILE__
#define FAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class MusicItem;
class FavoriteItemWidget;
class UserMutex;
class PlayerListWidget;
class PlayerWindow;

class FavoriteWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	FavoriteItemWidget *selectFavorite = nullptr;
	std::vector< FavoriteItemWidget * > favoriteVector;

public:
	FavoriteWidget( QWidget *parent );

protected:
	bool deleteResource( ) override;

public:
	~FavoriteWidget( ) override;
	virtual void updateAppMusicManageInof( const std::vector< std::pair< FavoriteItemWidget *, std::vector< MusicItem * > > > &vector );
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	virtual void updateLayout( );

	virtual bool resetFavoriteItem( const std::vector< FavoriteItemWidget * > &favorite_vector );
	virtual FavoriteItemWidget * getSelectItem( const QString &name ) const;
	virtual FavoriteItemWidget * getSelectItem( const QPoint &pos ) const;

protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void signal_update_layout_over( );
	void signal_update_item_over( );

	void signal_click_favorite_Item( FavoriteItemWidget *label_widget );

	void signal_favorite_Item_pop_menu( FavoriteItemWidget *label_widget );
};

#endif // FAVORITEWIDGET_H_H_HEAD__FILE__
