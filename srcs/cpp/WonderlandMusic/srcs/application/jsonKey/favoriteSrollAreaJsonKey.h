#ifndef FAVORITESROLLAREAJSONKEY_H_H_HEAD__FILE__
#define FAVORITESROLLAREAJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class FavoriteSrollAreaJsonKey : public IJsonKey{
	QString objectName;
	QString width;
	QString height;
public:
	bool init( ) override;

	virtual const QString & getWidth( ) const;

	virtual const QString & getObjectName( ) const;

	virtual const QString & getHeight( ) const;
};

#endif // FAVORITESROLLAREAJSONKEY_H_H_HEAD__FILE__
