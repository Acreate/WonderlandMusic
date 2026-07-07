#ifndef FAVORITEITEMJSONKEY_H_H_HEAD__FILE__
#define FAVORITEITEMJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class FavoriteItemJsonKey : public IJsonKey {
	QString favoriteItemArrayObject;
	QString favoriteItemArray;
	QString favoriteItemCount;
	QString favoriteName;
	QString musicCount;
	QString musicArray;

public:
	bool init( ) override;
	virtual const QString & getFavoriteItemArray( ) const;
	virtual const QString & getFavoriteItemCount( ) const;
	virtual const QString & getFavoriteName( ) const;
	virtual const QString & getMusicCount( ) const;
	virtual const QString & getMusicArray( ) const;
	virtual const QString & getFavoriteItemArrayObject( ) const;
};
#endif // FAVORITEITEMJSONKEY_H_H_HEAD__FILE__
