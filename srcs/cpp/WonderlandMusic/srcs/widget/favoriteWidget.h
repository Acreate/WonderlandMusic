#ifndef FAVORITEWIDGET_H_H_HEAD__FILE__
#define FAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"
class FavoriteItem;
class MusicItem;
class FavoriteItemWidget;
class UserMutex;
class PlayerListWidget;
class PlayerWindow;

class FavoriteWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	FavoriteItem *rootItem = nullptr;
	FavoriteItem *selectFavorite = nullptr;
	std::vector< FavoriteItem * > favoriteVector;

public:
	FavoriteWidget( QWidget *parent );

protected:
	bool deleteResource( ) override;

public:
	~FavoriteWidget( ) override;
	virtual FavoriteItem * getSelectFavorite( ) const;
	virtual void setSelectFavorite( FavoriteItem *const select_favorite );
	virtual void updateAppMusicManageInof( const std::vector< FavoriteItem * > &vector );
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
	virtual const std::vector< FavoriteItem * > & getFavoriteVector( ) const;
	virtual void updateLayout( );
	virtual bool resetFavoriteItem( const std::vector< FavoriteItem * > &favorite_vector );
	virtual FavoriteItem * getSelectItem( const QString &name ) const;
	virtual FavoriteItem * getSelectItem( const QPoint &pos ) const;

protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;

private Q_SLOTS:
	void slot_change_name_finished( );
	void slot_change_vector_finished( );
	void slot_destroyed( QObject *delete_ptr );
	void slot_update_favorite_item( const FavoriteItemWidget *favorite_widget );
Q_SIGNALS:
	void signal_update_layout_over( );
	void signal_update_item_over( );
	void signal_click_favorite_Item( FavoriteItem *label_widget );
	void signal_favorite_Item_pop_menu( FavoriteItem *label_widget );
};
#endif // FAVORITEWIDGET_H_H_HEAD__FILE__
