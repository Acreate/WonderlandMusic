#ifndef MUSICLISTMENUTRANSLATE_H_H_HEAD__FILE__
#define MUSICLISTMENUTRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class MusicListMenuTranslate : public ITranslate {
public:
	bool init( ) override;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( MusicListMenu );
}
#endif // MUSICLISTMENUTRANSLATE_H_H_HEAD__FILE__
