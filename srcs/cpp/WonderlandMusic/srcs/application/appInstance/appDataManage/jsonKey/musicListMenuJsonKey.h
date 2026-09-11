#ifndef MUSICLISTMENUJSONKEY_H_H_HEAD__FILE__
#define MUSICLISTMENUJSONKEY_H_H_HEAD__FILE__
#include <interface/iJsonKey.h>

class MusicListMenuJsonKey : public IJsonKey {
public:
	bool init( ) override;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicListMenu );
}

#endif // MUSICLISTMENUJSONKEY_H_H_HEAD__FILE__
