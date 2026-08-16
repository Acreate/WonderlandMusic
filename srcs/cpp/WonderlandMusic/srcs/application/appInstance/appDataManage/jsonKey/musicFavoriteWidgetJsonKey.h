#ifndef MUSICFAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__
#define MUSICFAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__
#include "../../../../interface/iJsonKey.h"

class MusicFavoriteWidgetJsonKey : public IJsonKey {
	QString countKey;
	QString favoriteVectorKey;
public:
	bool init( ) override;
	virtual const QString & getCountKey( ) const;
	virtual const QString & getFavoriteVectorKey( ) const;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicFavoriteWidget );
}
#endif // MUSICFAVORITEWIDGETJSONKEY_H_H_HEAD__FILE__
