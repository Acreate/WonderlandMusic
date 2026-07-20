#ifndef FAVORITEITEM_H_H_HEAD__FILE__
#define FAVORITEITEM_H_H_HEAD__FILE__
#include <QString>
class FavoriteWindow;

class FavoriteItem {
	QString name;
	FavoriteWindow *favoriteWindow;

public:
	virtual ~FavoriteItem( );
	FavoriteItem( FavoriteWindow *favorite_window, const QString &name );
	virtual const QString & getName( ) const;
	virtual void setName( const QString &name );
};
#endif // FAVORITEITEM_H_H_HEAD__FILE__
