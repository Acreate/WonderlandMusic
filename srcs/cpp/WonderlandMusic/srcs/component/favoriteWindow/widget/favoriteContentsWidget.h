#ifndef FAVORITECONTENTSWIDGET_H_H_HEAD__FILE__
#define FAVORITECONTENTSWIDGET_H_H_HEAD__FILE__
#include <QWidget>
#include "../../../interface/iAppCore.h"

class FavoriteContentsWidget : public QWidget, public IAppCore {
	Q_OBJECT;

public:
	FavoriteContentsWidget( QWidget *parent ) : QWidget( parent ) {
	}

	~FavoriteContentsWidget( ) override {
		deleteResource( );
	}

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // FAVORITECONTENTSWIDGET_H_H_HEAD__FILE__
