#ifndef MUSICFAVORITEMENUJSONKEY_H_H_HEAD__FILE__
#define MUSICFAVORITEMENUJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class MusicFavoriteMenuJsonKey : public IJsonKey {
public:
	bool init( ) override;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicFavoriteMenu );
};
#endif // MUSICFAVORITEMENUJSONKEY_H_H_HEAD__FILE__
