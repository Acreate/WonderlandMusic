#ifndef MUSICWINDOWJSONKEY_H_H_HEAD__FILE__
#define MUSICWINDOWJSONKEY_H_H_HEAD__FILE__
#include "../../interface/iJsonKey.h"

class MusicWindowJsonKey : public IJsonKey {
public:
	bool init( ) override;
};

namespace AppJsonKeyTools {
	Declaration_Get_JsonKey( MusicWindow );
};
#endif // MUSICWINDOWJSONKEY_H_H_HEAD__FILE__
