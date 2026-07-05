#ifndef FAVORITESROLLAREA_H_H_HEAD__FILE__
#define FAVORITESROLLAREA_H_H_HEAD__FILE__
#include <QScrollArea>

#include "../interface/iAppCore.h"

class FavoriteWidget;

class FavoriteSrollArea : public QScrollArea, public IAppCore {
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
};

#endif // FAVORITESROLLAREA_H_H_HEAD__FILE__
