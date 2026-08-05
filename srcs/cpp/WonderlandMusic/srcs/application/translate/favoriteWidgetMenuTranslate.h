#ifndef FAVORITEWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
#define FAVORITEWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class FavoriteWidgetMenuTranslate : public ITranslate {
public:
	bool init( ) override;
};

namespace AppTranslateTools {
	Declaration_Get_Translate( FavoriteWidgetMenu );
}
#endif // FAVORITEWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
