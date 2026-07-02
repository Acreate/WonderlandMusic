#ifndef FAVORITEWIDGETTRANSLATE_H_H_HEAD__FILE__
#define FAVORITEWIDGETTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class FavoriteWidgetTranslate : public ITranslate {
	QString defautFavoriteName;

public:
	bool init( ) override;

	virtual const QString & getDefautFavoriteName( ) const;
};

#endif // FAVORITEWIDGETTRANSLATE_H_H_HEAD__FILE__
