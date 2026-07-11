#ifndef ADDFAVORITEWINDOW_H_H_HEAD__FILE__
#define ADDFAVORITEWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>
#include "../interface/iAppCore.h"
class AddFavoriteItemWidget;

class AddFavoriteWindow : public QMainWindow, public IAppCore {
	Q_OBJECT;

protected:
	AddFavoriteItemWidget *addFavoriteItemWidget = nullptr;

protected:
	bool deleteResource( ) override;

public:
	AddFavoriteWindow( );
	AddFavoriteWindow( QWidget *parent );
	~AddFavoriteWindow( ) override;

	virtual AddFavoriteItemWidget * getAddFavoriteItemWidget( ) const;
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
};
#endif // ADDFAVORITEWINDOW_H_H_HEAD__FILE__
