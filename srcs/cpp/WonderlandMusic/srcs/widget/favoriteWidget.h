#ifndef FAVORITEWIDGET_H_H_HEAD__FILE__
#define FAVORITEWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class UserMutex;
class LabelWidget;
class PlayerListWidget;
class FavoriteItemWidget;
class PlayerWindow;

class FavoriteWidget : public QWidget, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	LabelWidget *rootFavorite = nullptr;
	LabelWidget *selectFavorite = nullptr;
	std::vector< LabelWidget * > favoriteVector;

public:
	FavoriteWidget( QWidget *parent );

protected:
	bool deleteResource( ) override;

	virtual void deleteFavoriteItem( );

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

	~FavoriteWidget( ) override;

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	virtual void updateLayout( );

	virtual bool appendFavoriteItem( const QString &create_favorite_name );

	virtual bool removeFavoriteItem( const QString &remove_favorite_name );

	virtual bool resetFavoriteItem( const std::vector< QString > &create_favorite_vector );
	virtual LabelWidget * getSelectItem( const QString &name ) const;
	virtual LabelWidget * getSelectItem( const QPoint &pos ) const;

protected:
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	void signal_update_layout_over( );

	void signal_click_favorite_Item( LabelWidget *label_widget );

	void signal_favorite_Item_pop_menu( LabelWidget *label_widget );
};

#endif // FAVORITEWIDGET_H_H_HEAD__FILE__
