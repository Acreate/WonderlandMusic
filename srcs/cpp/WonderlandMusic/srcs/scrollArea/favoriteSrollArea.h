#ifndef FAVORITESROLLAREA_H_H_HEAD__FILE__
#define FAVORITESROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

#include "../interface/iAppCore.h"
#include "../interface/iAppJsonData.h"

class FavoriteWidget;

class FavoriteSrollArea : public QScrollArea, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	FavoriteWidget *favoriteWidget = nullptr;

public:
	FavoriteSrollArea( QWidget *parent );

	~FavoriteSrollArea( ) override;

	virtual FavoriteWidget * getFavoriteWidget( ) const;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};

#endif // FAVORITESROLLAREA_H_H_HEAD__FILE__
