#ifndef FAVORITELISTWIDGET_H_H_HEAD__FILE__
#define FAVORITELISTWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../../../interface/iAppCore.h"

class FavoriteListWidget : public QWidget, public IAppCore {
	Q_OBJECT;

public:
	FavoriteListWidget( QWidget *parent ) : QWidget( parent ) {
	}

	~FavoriteListWidget( ) override {
		deleteResource( );
	}

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // FAVORITELISTWIDGET_H_H_HEAD__FILE__
