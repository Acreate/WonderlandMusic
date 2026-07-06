#ifndef FAVORITESROLLAREAJSONKEY_H_H_HEAD__FILE__
#define FAVORITESROLLAREAJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class FavoriteSrollAreaJsonKey : public IJsonKey{
	QString width;
public:
	bool init( ) override;

	virtual const QString & getWidth( ) const;
};

#endif // FAVORITESROLLAREAJSONKEY_H_H_HEAD__FILE__
