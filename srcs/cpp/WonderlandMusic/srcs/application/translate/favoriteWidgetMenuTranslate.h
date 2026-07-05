#ifndef FAVORITEWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
#define FAVORITEWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
#include "../../interface/iTranslate.h"

class FavoriteWidgetMenuTranslate : public ITranslate {
	QString addFavorite;
	QString deleteFavorite;
	QString changeFavorite;

public:
	bool init( ) override;

	virtual const QString & getAddFavorite( ) const;

	virtual const QString & getDeleteFavorite( ) const;

	virtual const QString & getChangeFavorite( ) const;
};

#endif // FAVORITEWIDGETMENUTRANSLATE_H_H_HEAD__FILE__
