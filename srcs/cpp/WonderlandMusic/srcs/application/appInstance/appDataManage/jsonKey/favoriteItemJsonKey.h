#ifndef FAVORITEITEMJSONKEY_H_H_HEAD__FILE__
#define FAVORITEITEMJSONKEY_H_H_HEAD__FILE__
#include "../../../../interface/iJsonKey.h"

class FavoriteItemJsonKey : public IJsonKey {
	QString musicCountKey;
	QString favoriteNameKey;

public:
	bool init( ) override;
	virtual const QString & getMusicCountKey( ) const;
	virtual const QString & getFavoriteNameKey( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( FavoriteItem );
}

#endif // FAVORITEITEMJSONKEY_H_H_HEAD__FILE__
