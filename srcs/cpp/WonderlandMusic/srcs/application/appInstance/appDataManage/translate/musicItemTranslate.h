#ifndef MUSICITEMTRANSLATE_H_H_HEAD__FILE__
#define MUSICITEMTRANSLATE_H_H_HEAD__FILE__
#include <interface/iTranslate.h>

class MusicItemTranslate : public ITranslate {
public:
	bool init( ) override;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( MusicItem );
}
#endif // MUSICITEMTRANSLATE_H_H_HEAD__FILE__
